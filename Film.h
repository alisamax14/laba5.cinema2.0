#ifndef FILM_H
#define FILM_H

#include <string>
#include <iostream>

class Film {
private:
    int id;
    std::string title;
    std::string genre;
    int duration;     // в минутах
    double rating;    // 0.0-10.0
    int year;

public:
    // Конструкторы
    Film();
    Film(int id, const std::string& title, const std::string& genre, 
         int duration, double rating, int year);
    
    // Геттеры
    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getDuration() const;
    double getRating() const;
    int getYear() const;
    
    // Сеттеры с валидацией
    void setId(int newId);
    void setTitle(const std::string& newTitle);
    void setGenre(const std::string& newGenre);
    void setDuration(int newDuration);     // проверка > 0
    void setRating(double newRating);      // проверка 0.0-10.0
    void setYear(int newYear);             // проверка 1888-2026
    
    // Ввод/вывод
    void input();           
    void display() const;
    
    // Операторы
    bool operator==(int filmId) const;
};

// Вспомогательная функция для безопасного ввода чисел
template<typename T>
T safeInput(const std::string& prompt, T minValue, T maxValue);

#endif
