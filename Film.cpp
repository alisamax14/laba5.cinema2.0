#include "Film.h"
#include <limits>
#include <string>
#include <sstream>

// Конструктор по умолчанию
Film::Film() : id(0), duration(0), rating(0.0), year(0) {}

// Конструктор с параметрами
Film::Film(int id, const std::string& title, const std::string& genre,
           int duration, double rating, int year)
    : id(id), title(title), genre(genre), duration(duration), 
      rating(rating), year(year) {}

// Геттеры
int Film::getId() const { return id; }
std::string Film::getTitle() const { return title; }
std::string Film::getGenre() const { return genre; }
int Film::getDuration() const { return duration; }
double Film::getRating() const { return rating; }
int Film::getYear() const { return year; }

// Сеттеры с валидацией
void Film::setId(int newId) { id = newId; }
void Film::setTitle(const std::string& newTitle) { title = newTitle; }
void Film::setGenre(const std::string& newGenre) { genre = newGenre; }

void Film::setDuration(int newDuration) {
    if (newDuration > 0) {
        duration = newDuration;
    } else {
        std::cout << "Ошибка: длительность должна быть положительной. Установлено значение 60.\n";
        duration = 60;
    }
}

void Film::setRating(double newRating) {
    if (newRating >= 0.0 && newRating <= 10.0) {
        rating = newRating;
    } else {
        std::cout << "Ошибка: рейтинг должен быть в диапазоне 0.0-10.0. Установлено значение 5.0.\n";
        rating = 5.0;
    }
}

void Film::setYear(int newYear) {
    if (newYear >= 1888 && newYear <= 2026) {
        year = newYear;
    } else {
        std::cout << "Ошибка: год должен быть в диапазоне 1888-2026. Установлено значение 2000.\n";
        year = 2000;
    }
}

// Вспомогательная функция для безопасного ввода чисел
template<typename T>
T safeInput(const std::string& prompt, T minValue, T maxValue) {
    T value;
    std::string input;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        std::stringstream ss(input);
        if (ss >> value && value >= minValue && value <= maxValue) {
            char remaining;
            if (!(ss >> remaining)) {
                return value;
            }
        }
        std::cout << "Ошибка! Введите число от " << minValue << " до " << maxValue << ": ";
    }
}

// Ввод данных от пользователя с защитой от некорректного ввода
void Film::input() {
    std::cout << "Введите название фильма: ";
    std::getline(std::cin, title);
    
    std::cout << "Введите жанр: ";
    std::getline(std::cin, genre);
    
    duration = safeInput<int>("Введите длительность (в минутах, >0): ", 1, 600);
    rating = safeInput<double>("Введите рейтинг (0.0-10.0): ", 0.0, 10.0);
    year = safeInput<int>("Введите год выпуска (1888-2026): ", 1888, 2026);
}

// Вывод фильма на экран
void Film::display() const {
    std::cout << id << " | " 
              << title;
    for (int i = title.length(); i < 28; i++) std::cout << " ";
    std::cout << " | " << genre;
    for (int i = genre.length(); i < 12; i++) std::cout << " ";
    std::cout << " | " << duration << "  | " << rating << "   | " << year;
}

bool Film::operator==(int filmId) const {
    return id == filmId;
}

// Явная инстанциация для нужных типов
template int safeInput<int>(const std::string&, int, int);
template double safeInput<double>(const std::string&, double, double);
