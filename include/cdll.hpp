#pragma once

template <typename T>
struct node
{
    T data;
    node *next;
    node *prev;
};

template <typename T>
class cdll
{
public:
    cdll() : sentinel_(new node<T>)
    {
        sentinel_->next = sentinel_;
        sentinel_->prev = sentinel_;
    }
    ~cdll()
    {
        clear();
        delete sentinel_;
    }

    void insert(const T &value)
    {
        node<T> *newNode = new node<T>;
        newNode->data = value;

        newNode->next = sentinel_->next;
        newNode->prev = sentinel_;
        sentinel_->next->prev = newNode;
        sentinel_->next = newNode;
    }

    node<T> *next(node<T> *current)
    {
        if (current->next == sentinel_)
        {
            // If list is empty, return nullptr
            if (isEmpty())
                return nullptr;
            // Otherwise loop back to first node
            return sentinel_->next;
        }
        return current->next;
    }

    node<T> *prev(node<T> *current)
    {
        if (current->prev == sentinel_)
        {
            // If list is empty, return nullptr
            if (isEmpty())
                return nullptr;
            // Otherwise loop back to last node
            return sentinel_->prev;
        }
        return current->prev;
    }

    node<T> *head()
    {
        if (sentinel_->next == sentinel_)
            return nullptr;
        return sentinel_->next;
    }

    node<T> *tail()
    {
        if (sentinel_->prev == sentinel_)
            return nullptr;
        return sentinel_->prev;
    }

    bool isEmpty() const
    {
        return sentinel_->next == sentinel_;
    }

    void clearAll()
    {
        clear();
    }

private:
    node<T> *sentinel_;

    void clear()
    {
        node<T> *current = sentinel_->next;
        while (current != sentinel_)
        {
            node<T> *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        sentinel_->next = sentinel_;
        sentinel_->prev = sentinel_;
    }
};