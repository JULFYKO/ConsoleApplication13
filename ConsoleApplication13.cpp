#include <iostream>
using namespace std;

template <typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

    void handleError(const char* message) const {
        cout << "Error: " << message << endl;
    }

public:
    Array(int initialSize = 0, int growStep = 1)
        : size(0), capacity(initialSize), grow(growStep) {
        if (capacity < 0 || grow <= 0) {
            handleError("Invalid initial size or grow value");
            capacity = 0;
            grow = 1;
        }
        data = (capacity > 0) ? new T[capacity] : nullptr;
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return capacity;
    }

    void SetSize(int newSize, int growStep = 1) {
        if (newSize < 0 || growStep <= 0) {
            handleError("Invalid size or grow value");
            return;
        }

        grow = growStep;
        if (newSize > capacity) {
            T* newData = new T[newSize];
            for (int i = 0; i < size; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newSize;
        }
        else {
            size = min(size, newSize);
            capacity = newSize;
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            T* newData = (size > 0) ? new T[size] : nullptr;
            for (int i = 0; i < size; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            handleError("Index out of range");
            return T();
        }
        return data[index];
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) {
            handleError("Index out of range");
            return;
        }
        data[index] = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            handleError("Index out of range");
            static T dummy = T();
            return dummy;
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            handleError("Index out of range");
            static T dummy = T();
            return dummy;
        }
        return data[index];
    }

    void Add(const T& value) {
        if (size >= capacity)
            SetSize(capacity + grow, grow);
        data[size++] = value;
    }

    void Append(const Array& other) {
        SetSize(size + other.size, grow);
        for (int i = 0; i < other.size; ++i)
            data[size++] = other.data[i];
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            grow = other.grow;
            data = new T[capacity];
            for (int i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    T* GetData() const {
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            handleError("Index out of range");
            return;
        }
        if (size >= capacity)
            SetSize(capacity + grow, grow);
        for (int i = size; i > index; --i)
            data[i] = data[i - 1];
        data[index] = value;
        ++size;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            handleError("Index out of range");
            return;
        }
        for (int i = index; i < size - 1; ++i)
            data[i] = data[i + 1];
        --size;
    }

    void Print() const {
        if (IsEmpty()) {
            cout << "Array is empty." << endl;
            return;
        }
        cout << "Array elements: ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array<int> arr(5, 3);
    arr.Add(10);
    arr.Add(20);
    arr.Add(30);

    arr.Print();

    arr.SetAt(1, 50);
    arr.Print();

    arr.InsertAt(1, 40);
    arr.Print();

    arr.RemoveAt(2);
    arr.Print();

    return 0;
}
