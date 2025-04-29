# IMDB Low-Level Design (LLD)

A lightweight backend system for managing movies, users, and reviews, inspired by IMDb.  
**Target Audience:** Developers practicing Low-Level Design (LLD) and backend service design.

---

## Requirements

- Users can register as **Free Reviewers** or **Paid Reviewers**.
- **Free Reviewers** can submit only 2 movie reviews per day.
- **Paid Reviewers** can submit unlimited reviews.
- Users can:
  - Retrieve the **top-rated movie** for a particular year.
  - View **ratings** they have given.

---

## Additional Requirements

- If a user tries to review a movie that doesn't exist, an appropriate exception (`MovieNotFoundException`) is thrown.

---

## Queries

- `add_movie(movieName, year)`
- `add_user(userId, userType)`
- `add_review(movieName, userId, rating, reviewText)`
- `user_query(year)`

---

## Queries Example

```bash
add_movie(Movie1, 2012)
add_movie(Movie2, 2013)
add_movie(Movie3, 2015)
add_movie(Movie4, 2012)
add_movie(Movie5, 2014)
add_movie(Movie6, 2013)
add_movie(Movie7, 2015)

add_user(1, FREE)
add_user(2, PAID)
add_user(3, PAID)
add_user(4, FREE)
add_user(5, FREE)

add_review(Movie1, 1, 5, good movie)
add_review(Movie1, 4, 5, good movie)
add_review(Movie1, 3, 5, good movie)
add_review(Movie2, 2, 4, average movie)
add_review(Movie3, 3, 3, not good movie)
add_review(Movie4, 4, 4, average movie)
add_review(Movie1, 5, 2, bad movie)
add_review(Movie3, 1, 4, average movie)
add_review(Movie5, 1, 2, bad movie)
add_review(Movie5, 2, 1, very bad movie)
add_review(Movie3, 2, 5, good movie)
add_review(Movie6, 3, 1, very bad movie)
add_review(Movie7, 4, 5, good movie)
add_review(Movie7, 5, 2, bad movie)

user_query(2012)
user_query(2013)
user_query(2014)
user_query(2015)

```

---

## Project Structure

- `/main`
  - `/model`
    - `User`
    - `Movie`
    - `Review`
  - `/service`
    - `MovieService`
    - `UserService`
  - `/exception`
    - `MovieNotFoundException`
  - `/utils`
    - `CommonUtils`

---

## Models

```cpp
#include <vector>
#include <string>
using namespace std;

enum Rating { ONE = 1, TWO, THREE, FOUR, FIVE };

class Review {
public:
    int      id;
    string   text;
    Rating   rating;
    int      movieId;
    int      userId;
};

class User {
public:
    int            id;
    UserType       type;           // FREE or PAID
    vector<Review> reviewList;
};

class Movie {
public:
    int            id;
    string         name;
    string         year;
    vector<Review> reviewList;
    double         averageRating;
};

```

## Services / Controllers

```cpp
class MovieService {
public:
    void addMovie(const string& movieName, const string& year);
};

class UserService {
public:
    void addReview(const string& movieName, int userId, Rating rating, const string& text);
    vector<Movie> userQuery(int year);
};
```

## Exception

```cpp
class MovieNotFoundException : public std::exception {
    const char* what() const noexcept override {
        return "Movie not found";
    }
};

```

