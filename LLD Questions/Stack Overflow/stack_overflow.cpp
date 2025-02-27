#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Forward declarations
class User;
class Post;
class Answer;
class Question;

class Comment {
public:
    string content;
    User* author;
    Post* post;
    time_t createdAt;
    Comment(string content, User* author, Post* post) {
        this->author = author;
        this->content = content;
        this->post = post;
        this->createdAt = time(0);
    }
    string getDate() {
        char buffer[80];
        struct tm* timeInfo = localtime(&createdAt);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
        return string(buffer);
    }
};

class Post {
public:
    int id;
    string content;
    User* author;
    unordered_set<User*> upVotes;
    unordered_set<User*> downVotes;
    vector<Comment*> comments;
    time_t createdAt;

    Post(int id, string content, User* author) {
        this->id = id;
        this->content = content;
        this->author = author;
        this->createdAt = time(0);
    }
    
    virtual ~Post() {} // Change: Added virtual destructor for proper cleanup

    string getDate() {
        char buffer[80];
        struct tm* timeInfo = localtime(&createdAt);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
        return string(buffer);
    }
    
    // Change: Updated upVote to update reputation (assumed +10 for an upvote)
    void upVote(User* user);
    
    // Change: Updated downVote to update reputation (assumed -2 for a downvote)
    void downVote(User* user);
    
    // Change: Removed console output from getUpVotes and getDownVotes for better design
    int getUpVotes() {
        return upVotes.size();
    }
    int getDownVotes() {
        return downVotes.size();
    }
};

class User {
public:
    string name;
    string email;
    int reputation;
    User(string name, string email) {
        this->name = name;
        this->email = email;
        this->reputation = 0; // Change: Initialize reputation
    }
    void updateReputation(int points) {
        reputation += points;
    }
};

class Question : public Post {
public:
    string title;
    vector<Answer*> answers;
    vector<string> tags;
    Question(int id, string content, string title, User* author, vector<string> tags)
        : Post(id, content, author) {
        this->title = title;
        this->tags = tags;
    }
};

class Answer : public Post {
public:
    Question* question;
    Answer(int id, string content, User* author, Question* question)
        : Post(id, content, author) {
        this->question = question;
    }
};

// Change: Implementation of upVote and downVote with reputation update
void Post::upVote(User* user) {
    if (upVotes.find(user) == upVotes.end()) { // Avoid duplicate upvotes
        upVotes.emplace(user);
        downVotes.erase(user);
        // Change: Update the post's author's reputation (assumed +10)
        author->updateReputation(10);
    }
}

void Post::downVote(User* user) {
    if (downVotes.find(user) == downVotes.end()) { // Avoid duplicate downvotes
        downVotes.emplace(user);
        upVotes.erase(user);
        // Change: Update the post's author's reputation (assumed -2)
        author->updateReputation(-2);
    }
}



// Change: Updated SearchStrategy interface with corrected method name "search"
class SearchStrategy {
public:
    virtual vector<int> search(const string& searchParameter, const unordered_set<Question*>& questions) = 0;
};

class SearchByTag : public SearchStrategy {
public:
    vector<int> search(const string& searchParameter, const unordered_set<Question*>& questions) override {
        vector<int> res;
        for (auto question : questions) {
            if (find(question->tags.begin(), question->tags.end(), searchParameter) != question->tags.end()) {
                res.push_back(question->id);
            }
        }
        return res;
    }
};

class SearchByUser : public SearchStrategy {
public:
    vector<int> search(const string& searchParameter, const unordered_set<Question*>& questions) override {
        vector<int> res;
        for (auto question : questions) {
            if (question->author->name == searchParameter) {
                res.push_back(question->id);
            }
        }
        return res;
    }
};

class StackOverflow {
public:
    static int id;
    unordered_set<Question*> questions;
    unordered_map<int, Question*> idMap;

    void postQuestion(string content, string title, User* author, vector<string> tags) {
        int nextId = getId();
        Question* question = new Question(nextId, content, title, author, tags);
        questions.emplace(question);
        idMap[nextId] = question;
    }

    void postAnswer(string content, User* author, int questionId) {
        int nextId = getId();
        // Change: Check if the question exists before posting an answer
        if (idMap.find(questionId) == idMap.end()) {
            cout << "Question with ID " << questionId << " does not exist." << endl;
            return;
        }
        Answer* answer = new Answer(nextId, content, author, idMap[questionId]);
        // Change: Add the answer to the question's answers vector
        idMap[questionId]->answers.push_back(answer);
    }

    void removeQuestion(int id) {
        questions.erase(idMap[id]);
        idMap.erase(id);
    }

    vector<int> findQuestion(string searchParameter, SearchStrategy* searchStrategy) {
        vector<int> res = searchStrategy->search(searchParameter, questions);
        for (auto &i : res)
            displayQuestion(i);
        return res;
    }

    void displayQuestion(int id) {
        if (idMap.find(id) == idMap.end()) return;
        Question* question = idMap[id];
        cout << "Title: " << question->title << "\n";
        cout << "Content: " << question->content << "\n";
        cout << "ID: " << question->id << "\n";
        cout << "Author: " << question->author->name << "\n";
        cout << "Tags: ";
        for (auto& tag : question->tags)
            cout << tag << " ";
        cout << "\nUpVotes: " << question->getUpVotes() << " DownVotes: " << question->getDownVotes() << "\n";
        cout << "Posted at: " << question->getDate() << "\n";
        cout << "Answers:\n";
        for (auto &ans : question->answers) {
            cout << "\t" << ans->content << " by " << ans->author->name 
                 << " [UpVotes: " << ans->getUpVotes() << " DownVotes: " << ans->getDownVotes() << "]\n";
        }
        cout << "\n";
    }

    void displayAllQuestions() {
        for (auto &pair : idMap) {
            displayQuestion(pair.first);
        }
    }

    int getId() {
        return id++;
    }
};

int StackOverflow::id = 1; // Change: Initialize static id

int main() {
    User* dhaval = new User("Dhaval", "dhaval@gmail.com");
    User* taylor = new User("taylor", "taylor@gmail.com");
    StackOverflow* st = new StackOverflow();

    st->postQuestion("This is question 1 by dhaval", "Q1 Dhaval", dhaval, {"Question1", "Q1"});
    st->postQuestion("This is question 2 by dhaval", "Q2 Dhaval", dhaval, {"Question2", "Q2"});
    st->postAnswer("Answer1", taylor, 1);
    
    // Example: Upvoting and downvoting
    st->idMap[1]->upVote(taylor); // Taylor upvotes question 1
    if (!st->idMap[1]->answers.empty()) {
        st->idMap[1]->answers[0]->downVote(dhaval); // Dhaval downvotes the answer
    }
    
    st->displayAllQuestions();

    // Example: Searching
    SearchByTag searchTag;
    cout << "Search results for tag 'Q1':\n";
    st->findQuestion("Q1", &searchTag);
    
    SearchByUser searchUser;
    cout << "Search results for user 'Dhaval':\n";
    st->findQuestion("Dhaval", &searchUser);

    return 0;
}
