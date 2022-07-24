#include <iostream>
#include <cassert>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class MyList
{
public:
    MyList() // Конструктор по умолчанию, создаётся пустой список
    {
        elements_count = 0;
        first_ = NULL;
        last_ = NULL;
    }
    MyList(const int* array, const int& size) // Создаётся список с элементами из массива array
    {
        first_ = new element(array[0], NULL, NULL);
        last_ = first_;
        elements_count = 1;
        for (int i = 1; i < size; i++)
        {
            push_back(array[i]);
        }
    }

    ~MyList() // Деструктор, удаляет все элементы
    {
        if (elements_count == 0) return;
        if (elements_count == 1)
        {
            delete first_;
            return;
        }
        element* current = first_;
        for (int i = 0; i < elements_count - 1; i++)
        {
            current = current->next;
            delete current->prev;
        }
        delete last_;
    }

    void push_front(const int& value) // Вставка в начало
    {
        if (elements_count == 0)
        {
            this->first_ = new element(value, NULL, this->first_);
            last_ = first_;
        }
        elements_count += 1;
        this->first_ = new element(value, NULL, this->first_);
        this->first_->next->prev = this->first_;
    }
    void push_back(const int& value) // Вставка в конец
    {
        if (elements_count == 0)
        {
            this->first_ = new element(value, NULL, this->first_);
            last_ = first_;
        }
        elements_count += 1;
        this->last_ = new element(value, this->last_, NULL);
        this->last_->prev->next = this->last_;
    }

    int pop_front() // Получение значения первого элемента и удаление его из списка
    {
        assert(elements_count > 0);
        int for_return = first_->value;
        if (elements_count == 1)
        {
            delete first_;
            this->first_ = NULL;
            this->last_ = NULL;
            elements_count -= 1;
            return for_return;
        }
        elements_count -= 1;
        first_ = first_->next;
        delete first_->prev;
        first_->prev = NULL;
        return for_return;
    }
    int pop_back() // Получение значения последнего элемента и удаление его из списка
    {
        assert(elements_count > 0);
        int for_return = last_->value;
        if (elements_count == 1)
        {
            delete last_;
            this->first_ = NULL;
            this->last_ = NULL;
            elements_count -= 1;
            return for_return;
        }
        elements_count -= 1;
        last_ = last_->prev;
        delete last_->next;
        last_->next = NULL;
        return for_return;
    }

    int indexOf(const int& value) const // Индекс первого по порядку элемента со значением value. Если не найден, то вернуть -1 
    {
        element* current = first_;
        for (int i = 0; i < elements_count; i++)
        {
            if (current->value == value) return i;
            current = current->next;
        }
        return -1;
    }
    void insert(const int& index, const int& value) // Создание элемента с индексом index и значением value
    {
        assert(index >= 0);
        assert(index <= elements_count);
        if (index == 0)
        {
            push_front(value);
            return;
        }
        if (index == 0)
        {
            push_front(elements_count);
            return;
        }
        elements_count += 1;
        element* current = first_;
        for (int i = 0; i < index; i++) current = current->next;
        element* element_insert = new element(value, current->prev, current);
        current->prev->next = element_insert;
        current->prev = element_insert;
    }
    void removeAt(const int& index) // Удаление элемента по индексу
    {
        assert(index >= 0);
        assert(index < elements_count);
        if (index == 0)
        {
            pop_front();
            return;
        }
        if (index == (elements_count - 1))
        {
            pop_back();
            return;
        }
        elements_count -= 1;
        element* current = first_;
        for (int i = 0; i < index; i++) current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete[] current;
    }

    int& operator[] (const int& index) // Получение ссылки на значение элемента с индексом index, чтобы можно было писать list[4] = 155; std::cout << list[4];
    {
        assert(index >= 0);
        assert(index < elements_count);
        element* current = first_;
        for (int i = 0; i < index; i++) current = current->next;
        return current->value;
    }
    const int& at(const int& index) const // Получение константной на значение элемента с индексом index
    {
        assert(index >= 0);
        assert(index < elements_count);
        element* current = first_;
        for (int i = 0; i < index; i++) current = current->next;
        return current->value;
    }

    bool isEmpty() const // Пустой ли список
    {
        return elements_count == 0;
    }
    int length() const // Получение кол-ва элемента в списке
    {
        return elements_count;
    }

    const int& first() const // Возвращает ссылку на значение первого элемента
    {
        assert(elements_count > 0);
        return first_->value;
    }
    const int& last() const // Возвращает ссылку на значение последнего элемента
    {
        assert(elements_count > 0);
        return last_->value;
    }

    void print()
    {
        if (elements_count == 0) {
            std::cout << "no elements\n";
            return;
        }
        element* current = first_;
        for (int i = 0; i < elements_count; i++)
        {
            std::cout << i << ':' << current->value << '\t';
            current = current->next;
        }
        std::cout << '\n';
    }

private:

    struct element
    {
        element()
        {
            next = NULL;
            prev = NULL;
            value = NULL;
        }
        element(int value, element* prev, element* next)
        {
            this->next = next;
            this->prev = prev;
            this->value = value;
        }
        element* next;
        element* prev;
        int value;
    };
    int elements_count;
    element* first_;
    element* last_;
};
void random_array(int* A, const int N) // Генератор рандомного не сортированного массива
{
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        int x = rand();
        x %= 1000; // здесь настраивать диапозон чисел
        A[i] = x;
    }
}
void programm()
{
    const int N = 10;
    int A[N];
    random_array(A, N);
    MyList Airat(A, N);
    std::cout << Airat.length() << '\n';
    Airat.print();
    std::cout << Airat.length() << '\n'
        << Airat.first() << ' ' << Airat.last() << ' ' << Airat.isEmpty() << '\n';
    while (Airat.length() != 0)
    {
        Airat.pop_back();
        Airat.print();
    }
    std::cout << Airat.length() << ' '
        << Airat.isEmpty() << '\n';
}
int main()
{
    programm();
    _CrtDumpMemoryLeaks();
    return 0;
}