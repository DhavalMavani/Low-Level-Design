#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

using namespace std;

// ----- Exceptions -----
class MovieNotFoundException : public runtime_error {
public:
    MovieNotFoundException(const string& msg) : runtime_error(msg) {}
};

class UserNotFoundException : public runtime_error {
public:
    UserNotFoundException(const string& msg) : runtime_error(msg) {}
};

class ReviewLimitExceededException : public runtime_error {
public:
    ReviewLimitExceededException(const string& msg) : runtime_error(msg) {}
};

// ----- Models -----
enum UserType { FREE, PAID };

class User {
public:
    User(int id, UserType type) : id(id), type(type), reviewsToday(0) {}
    int getId() const { return id; }
    UserType getType() const { return type; }
    int getReviewsToday() const { return reviewsToday; }
    void incrementReviews() { ++reviewsToday; }

private:
    int id;
    UserType type;
    int reviewsToday;
};

class Review {
public:
    Review(int userId, const string& movieName, int rating, const string& text)
        : userId(userId), movieName(movieName), rating(rating), text(text) {}

    int getUserId() const { return userId; }
    const string& getMovieName() const { return movieName; }
    int getRating() const { return rating; }
    const string& getText() const { return text; }

private:
    int userId;
    string movieName;
    int rating;
    string text;
};

class Movie {
public:
    Movie(const string& name, int year) : name(name), year(year) {}

    const string& getName() const { return name; }
    int getYear() const { return year; }
    const vector<Review*>& getReviews() const { return reviews; }
    void addReview(Review* rev) { reviews.push_back(rev); }

private:
    string name;
    int year;
    vector<Review*> reviews;  // store pointers to full Review objects
};

// ----- Views -----
class MovieView {
public:
    static void showTopMovie(const Movie& movie) {
        const auto& revs = movie.getReviews();
        if (revs.empty()) {
            cout << "No reviews for " << movie.getYear() << endl;
            return;
        }
        double sum = 0;
        for (auto* r : revs) sum += r->getRating();
        double avg = sum / revs.size();
        cout << "Top movie of " << movie.getYear()
             << ": " << movie.getName()
             << " (Avg Rating: " << avg << ")" << endl;
    }
};

class ReviewView {
public:
    static void showUserRatings(const vector<Review*>& reviews, int userId) {
        cout << "Ratings by user " << userId << ":\n";
        for (auto* rev : reviews) {
            if (rev->getUserId() == userId) {
                cout << "  " << rev->getMovieName()
                     << " -> " << rev->getRating() << "\n";
            }
        }
    }
};

// ----- Controllers -----
class MovieController {
    unordered_map<string, Movie*> movies;
public:
    ~MovieController() { for (auto &p : movies) delete p.second; }

    void addMovie(const string& name, int year) { movies[name] = new Movie(name, year); }

    Movie& getMovie(const string& name) {
        auto it = movies.find(name);
        if (!movies.count(name) ) throw MovieNotFoundException("Movie not found: " + name);
        return *it->second;
    }

    Movie* findTopMovieByYear(int year) {
        Movie* top = nullptr;
        double bestAvg = -1;
        for (auto& p : movies) {
            Movie* m = p.second;
            if (m->getYear() == year && !m->getReviews().empty()) {
                double sum = 0;
                for (auto* r : m->getReviews()) sum += r->getRating();
                double avg = sum / m->getReviews().size();
                if (avg > bestAvg) {
                    bestAvg = avg;
                    top = m;
                }
            }
        }
        return top;
    }
};

class UserController {
    unordered_map<int, User*> users;
public:
    ~UserController() {
        for (auto& p : users) delete p.second;
    }

    void addUser(int userId, UserType type) {
        users[userId] = new User(userId, type);
    }

    User& getUser(int userId) {
        auto it = users.find(userId);
        if (it == users.end()) throw UserNotFoundException("User not found: " + to_string(userId));
        return *it->second;
    }
};

class ReviewController {
    MovieController& movieCtrl;
    UserController& userCtrl;
    vector<Review*> reviews;
    const int FREE_LIMIT = 2;
public:
    ReviewController(MovieController& mc, UserController& uc) : movieCtrl(mc), userCtrl(uc) {}
    ~ReviewController() {
        for (auto* r : reviews) delete r;
    }

    void addReview(const string& movieName, int userId, int rating, const string& text) {
        User& user = userCtrl.getUser(userId);
        Movie& movie = movieCtrl.getMovie(movieName);
        if (user.getType() == FREE && user.getReviewsToday() >= FREE_LIMIT) {
            throw ReviewLimitExceededException("Free user " + to_string(userId) + " exceeded daily review limit");
        }
        user.incrementReviews();
        Review* rev = new Review(userId, movieName, rating, text);
        reviews.push_back(rev);
        movie.addReview(rev);
    }

    const vector<Review*>& getAllReviews() const { return reviews; }
};

// ----- Single Entry Point: IMDb Application -----
class IMDb {
    MovieController movieCtrl;
    UserController userCtrl;
    ReviewController reviewCtrl;
public:
    IMDb() : reviewCtrl(movieCtrl, userCtrl) {}

    void addMovie(const string& name, int year) {
        movieCtrl.addMovie(name, year);
    }
    void addUser(int userId, UserType type) {
        userCtrl.addUser(userId, type);
    }
    void addReview(const string& movieName, int userId, int rating, const string& text) {
        try {
            reviewCtrl.addReview(movieName, userId, rating, text);
        } catch (const exception& ex) {
            cout << "Error adding review: " << ex.what() << endl;
        }
    }
    void queryTopMovie(int year) {
        Movie* top = movieCtrl.findTopMovieByYear(year);
        if (top) {
            MovieView::showTopMovie(*top);
        } else {
            cout << "No movies found for year " << year << endl;
        }
    }
    void queryUserRatings(int userId) {
        ReviewView::showUserRatings(reviewCtrl.getAllReviews(), userId);
    }
};

int main() {
    IMDb imdb;
    imdb.addMovie("Movie1", 2012);
    imdb.addMovie("Movie2", 2013);
    imdb.addMovie("Movie3", 2015);
    imdb.addMovie("Movie4", 2012);
    imdb.addMovie("Movie5", 2014);
    imdb.addMovie("Movie6", 2013);
    imdb.addMovie("Movie7", 2015);
    imdb.addUser(1, FREE);
    imdb.addUser(2, PAID);
    imdb.addUser(3, PAID);
    imdb.addUser(4, FREE);
    imdb.addUser(5, FREE);
    imdb.addReview("Movie1", 1, 5, "good movie");
    imdb.addReview("Movie1", 4, 5, "good movie");
    imdb.addReview("Movie1", 3, 5, "good movie");
    imdb.addReview("Movie2", 2, 4, "average movie");
    imdb.addReview("Movie3", 3, 3, "not good movie");
    imdb.addReview("Movie4", 4, 4, "average movie");
    imdb.addReview("Movie1", 5, 2, "bad movie");
    imdb.addReview("Movie3", 1, 4, "average movie");
    imdb.addReview("Movie5", 1, 2, "bad movie");
    imdb.addReview("Movie5", 2, 1, "very bad movie");
    imdb.addReview("Movie3", 2, 5, "good movie");
    imdb.addReview("Movie6", 3, 1, "very bad movie");
    imdb.addReview("Movie7", 4, 5, "good movie");
    imdb.addReview("Movie7", 5, 2, "bad movie");
    imdb.queryTopMovie(2012);
    imdb.queryTopMovie(2013);
    imdb.queryTopMovie(2014);
    imdb.queryTopMovie(2015);
    return 0;
}
