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
        this->content = content;
        this->author = author;
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

    void updateReputation(int points) { reputation += points; }
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
    
    virtual ~Post() {}

    string getDate() {
        char buffer[80];
        struct tm* timeInfo = localtime(&createdAt);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
        return string(buffer);
    }
    
    void upVote(User* user) {
        if (upVotes.find(user) == upVotes.end()) {
            upVotes.emplace(user);
            downVotes.erase(user);
            author->updateReputation(10);
        }
    }
    
    void downVote(User* user) {
        if (downVotes.find(user) == downVotes.end()) {
            downVotes.emplace(user);
            upVotes.erase(user);
            author->updateReputation(-2);
        }
    }
    
    int getUpVotes() { return upVotes.size(); }

    int getDownVotes() { return downVotes.size(); }
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
        if (idMap.find(questionId) == idMap.end()) {
            cout << "Question with ID " << questionId << " does not exist." << endl;
            return;
        }
        Answer* answer = new Answer(nextId, content, author, idMap[questionId]);
        idMap[questionId]->answers.push_back(answer);
    }
    
    void postCommentOnQuestion(int questionId, string content, User* author) {
        if (idMap.find(questionId) == idMap.end()) {
            cout << "Question with ID " << questionId << " not found." << endl;
            return;
        }
        Comment* comment = new Comment(content, author, idMap[questionId]);
        idMap[questionId]->comments.push_back(comment);
    }
    
    void postCommentOnAnswer(int questionId, int answerId, string content, User* author) {
        if (idMap.find(questionId) == idMap.end()) {
            cout << "Question with ID " << questionId << " not found." << endl;
            return;
        }
        Question* q = idMap[questionId];
        Answer* foundAnswer = nullptr;
        for (auto ans : q->answers) {
            if (ans->id == answerId) {
                foundAnswer = ans;
                break;
            }
        }
        if (foundAnswer == nullptr) {
            cout << "Answer with ID " << answerId << " not found." << endl;
            return;
        }
        Comment* comment = new Comment(content, author, foundAnswer);
        foundAnswer->comments.push_back(comment);
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
        
        // Change: Display comments on the question
        if (!question->comments.empty()) {
            cout << "Question Comments:\n";
            for (auto comm : question->comments) {
                cout << "\t" << comm->author->name << " commented: " 
                     << comm->content << " at " << comm->getDate() << "\n";
            }
        }
        
        cout << "Answers:\n";
        for (auto &ans : question->answers) {
            cout << "\t" << ans->content << " by " << ans->author->name 
                 << " [UpVotes: " << ans->getUpVotes() << " DownVotes: " << ans->getDownVotes() << "]\n";
            if (!ans->comments.empty()) {
                cout << "\t Answer Comments:\n";
                for (auto comm : ans->comments) {
                    cout << "\t\t" << comm->author->name << " commented: " 
                         << comm->content << " at " << comm->getDate() << "\n";
                }
            }
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

int StackOverflow::id = 1;

int main() {
    User* dhaval = new User("Dhaval", "dhaval@gmail.com");
    User* taylor = new User("taylor", "taylor@gmail.com");
    StackOverflow* st = new StackOverflow();

    st->postQuestion("This is question 1 by Dhaval", "Q1 Dhaval", dhaval, {"Question1", "Q1"});
    st->postQuestion("This is question 2 by Dhaval", "Q2 Dhaval", dhaval, {"Question2", "Q2"});
    st->postAnswer("Answer1", taylor, 1);
    
    st->idMap[1]->upVote(taylor); // Taylor upvotes question 1
    if (!st->idMap[1]->answers.empty()) {
        st->idMap[1]->answers[0]->downVote(dhaval); // Dhaval downvotes the answer
    }
    
    st->postCommentOnQuestion(1, "This is a comment on question 1 by Taylor", taylor);
    int answerId = st->idMap[1]->answers[0]->id;
    st->postCommentOnAnswer(1, answerId, "This is a comment on the answer by Dhaval", dhaval);
    
    st->displayAllQuestions();

    return 0;
}
