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

    // Copy constructor
    cdll(const cdll &other) : sentinel_(new node<T>)
    {
        sentinel_->next = sentinel_;
        sentinel_->prev = sentinel_;

        // Copy all nodes from other
        node<T> *current = other.sentinel_->next;
        while (current != other.sentinel_)
        {
            insert(current->data);
            current = current->next;
        }
    }

    // Copy assignment operator
    cdll &operator=(const cdll &other)
    {
        if (this != &other)
        {
            clear();

            // Copy all nodes from other
            node<T> *current = other.sentinel_->next;
            while (current != other.sentinel_)
            {
                insert(current->data);
                current = current->next;
            }
        }
        return *this;
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

    // Insert at specific position (0-based index)
    // If position < 0 or position > size, inserts at beginning
    void insertAt(const T &value, int position)
    {
        if (position <= 0)
        {
            insert(value); // Insert at beginning
            return;
        }

        int currentSize = size();
        if (position >= currentSize)
        {
            // Insert at end
            node<T> *newNode = new node<T>;
            newNode->data = value;

            newNode->next = sentinel_;
            newNode->prev = sentinel_->prev;
            sentinel_->prev->next = newNode;
            sentinel_->prev = newNode;
            return;
        }

        // Insert at specific position
        node<T> *current = sentinel_->next;
        for (int i = 0; i < position && current != sentinel_; i++)
        {
            current = current->next;
        }

        node<T> *newNode = new node<T>;
        newNode->data = value;

        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
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

    int size() const
    {
        int count = 0;
        node<T> *current = sentinel_->next;
        while (current != sentinel_)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    // Get node at specific index (0-based)
    node<T> *getAt(int index)
    {
        if (index < 0 || isEmpty())
            return nullptr;

        node<T> *current = sentinel_->next;
        for (int i = 0; i < index && current != sentinel_; i++)
        {
            current = current->next;
        }

        return (current == sentinel_) ? nullptr : current;
    }

    // Remove a specific node
    void remove(node<T> *nodeToRemove)
    {
        if (!nodeToRemove || nodeToRemove == sentinel_)
            return;

        nodeToRemove->prev->next = nodeToRemove->next;
        nodeToRemove->next->prev = nodeToRemove->prev;
        delete nodeToRemove;
    }

    // Find node containing specific data
    node<T> *find(const T &value) const
    {
        node<T> *current = sentinel_->next;
        while (current != sentinel_)
        {
            if (current->data == value)
                return current;
            current = current->next;
        }
        return nullptr;
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