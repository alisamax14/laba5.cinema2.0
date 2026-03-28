#ifndef FILMARRAY_H
#define FILMARRAY_H

#include "Film.h"

class FilmArray {
private:
    Film* films;        // Динамический массив
    int capacity;       // Вместимость
    int size;           // Текущий размер
    
    void resize();      // Увеличение массива при необходимости
    void copyFrom(const FilmArray& other);
    void freeMemory();
    
public:
    // Конструкторы и деструктор
    FilmArray();
    FilmArray(const FilmArray& other);
    ~FilmArray();
    
    // Оператор присваивания
    FilmArray& operator=(const FilmArray& other);
    
    // Оператор доступа по индексу
    Film& operator[](int index);
    const Film& operator[](int index) const;
    
    // Основные операции
    void addFilm(const Film& film);
    void removeFilm(int id);
    Film& findFilm(int id);           // Возвращает ссылку вместо указателя
    int getSize() const;
    bool isEmpty() const;
    
    // Поиск и вывод
    void displayAll() const;
    void searchByGenre(const std::string& genre) const;
    void searchByRating(double minRating) const;
    void searchByYear(int year) const;
    
    // Редактирование
    void editFilm(int id);
    
    // Получение всех фильмов (для сохранения)
    const Film* getAllFilms() const;
    
    // Следующий ID
    int getNextId() const;
    
    // Исключение для случая, когда фильм не найден
    class FilmNotFoundException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Фильм не найден";
        }
    };
};

#endif
