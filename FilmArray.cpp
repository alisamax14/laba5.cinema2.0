#include "FilmArray.h"
#include <iostream>
#include <cstring>
#include <algorithm>

const int INITIAL_CAPACITY = 10;

FilmArray::FilmArray() : capacity(INITIAL_CAPACITY), size(0) {
    films = new Film[capacity];
}

FilmArray::FilmArray(const FilmArray& other) {
    copyFrom(other);
}

FilmArray::~FilmArray() {
    freeMemory();
}

void FilmArray::copyFrom(const FilmArray& other) {
    capacity = other.capacity;
    size = other.size;
    films = new Film[capacity];
    for (int i = 0; i < size; i++) {
        films[i] = other.films[i];
    }
}

void FilmArray::freeMemory() {
    delete[] films;
    films = nullptr;
}

FilmArray& FilmArray::operator=(const FilmArray& other) {
    if (this != &other) {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

Film& FilmArray::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return films[index];
}

const Film& FilmArray::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return films[index];
}

void FilmArray::resize() {
    capacity *= 2;
    Film* newFilms = new Film[capacity];
    for (int i = 0; i < size; i++) {
        newFilms[i] = films[i];
    }
    delete[] films;
    films = newFilms;
}

void FilmArray::addFilm(const Film& film) {
    if (size >= capacity) {
        resize();
    }
    films[size++] = film;
    std::cout << "Фильм успешно добавлен!\n";
}

void FilmArray::removeFilm(int id) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (films[i].getId() == id) {
            index = i;
            break;
        }
    }
    
    if (index != -1) {
        for (int i = index; i < size - 1; i++) {
            films[i] = films[i + 1];
        }
        size--;
        std::cout << "Фильм с ID " << id << " удален.\n";
    } else {
        std::cout << "Фильм с ID " << id << " не найден.\n";
    }
}

Film& FilmArray::findFilm(int id) {
    for (int i = 0; i < size; i++) {
        if (films[i].getId() == id) {
            return films[i];
        }
    }
    throw FilmNotFoundException();
}

int FilmArray::getSize() const {
    return size;
}

bool FilmArray::isEmpty() const {
    return size == 0;
}

void FilmArray::displayAll() const {
    if (isEmpty()) {
        std::cout << "База данных пуста.\n";
        return;
    }
    
    std::cout << "\n=== Список всех фильмов ===\n";
    std::cout << "ID  | Название                     | Жанр         | Длит. | Рейтинг | Год\n";
    std::cout << "----|------------------------------|--------------|-------|---------|-----\n";
    
    for (int i = 0; i < size; i++) {
        films[i].display();
        std::cout << "\n";
    }
    std::cout << "Всего фильмов: " << size << "\n";
}

void FilmArray::searchByGenre(const std::string& genre) const {
    std::cout << "\nРезультаты поиска по жанру '" << genre << "':\n";
    std::cout << "ID  | Название                     | Жанр         | Длит. | Рейтинг | Год\n";
    std::cout << "----|------------------------------|--------------|-------|---------|-----\n";
    
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (films[i].getGenre().find(genre) != std::string::npos) {
            films[i].display();
            std::cout << "\n";
            found++;
        }
    }
    std::cout << "\nНайдено фильмов: " << found << "\n";
}

void FilmArray::searchByRating(double minRating) const {
    std::cout << "\nРезультаты поиска с рейтингом >= " << minRating << ":\n";
    std::cout << "ID  | Название                     | Жанр         | Длит. | Рейтинг | Год\n";
    std::cout << "----|------------------------------|--------------|-------|---------|-----\n";
    
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (films[i].getRating() >= minRating) {
            films[i].display();
            std::cout << "\n";
            found++;
        }
    }
    std::cout << "\nНайдено фильмов: " << found << "\n";
}

void FilmArray::searchByYear(int year) const {
    std::cout << "\nРезультаты поиска за " << year << " год:\n";
    std::cout << "ID  | Название                     | Жанр         | Длит. | Рейтинг | Год\n";
    std::cout << "----|------------------------------|--------------|-------|---------|-----\n";
    
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (films[i].getYear() == year) {
            films[i].display();
            std::cout << "\n";
            found++;
        }
    }
    std::cout << "\nНайдено фильмов: " << found << "\n";
}

void FilmArray::editFilm(int id) {
    try {
        Film& film = findFilm(id);
        
        std::cout << "\nРедактирование фильма (ID: " << id << ")\n";
        std::cout << "Оставьте поле пустым (нажмите Enter), чтобы не изменять его.\n\n";
        
        std::string input;
        std::cin.ignore();
        
        // Редактирование названия
        std::cout << "Текущее название: " << film.getTitle() << "\n";
        std::cout << "Новое название: ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            film.setTitle(input);
        }
        
        // Редактирование жанра
        std::cout << "Текущий жанр: " << film.getGenre() << "\n";
        std::cout << "Новый жанр: ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            film.setGenre(input);
        }
        
        // Редактирование длительности
        std::cout << "Текущая длительность: " << film.getDuration() << "\n";
        std::cout << "Новая длительность (0 чтобы не менять): ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            int newDuration = std::stoi(input);
            if (newDuration != 0) {
                film.setDuration(newDuration);
            }
        }
        
        // Редактирование рейтинга
        std::cout << "Текущий рейтинг: " << film.getRating() << "\n";
        std::cout << "Новый рейтинг (0 чтобы не менять): ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            double newRating = std::stod(input);
            if (newRating != 0) {
                film.setRating(newRating);
            }
        }
        
        // Редактирование года
        std::cout << "Текущий год: " << film.getYear() << "\n";
        std::cout << "Новый год (0 чтобы не менять): ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            int newYear = std::stoi(input);
            if (newYear != 0) {
                film.setYear(newYear);
            }
        }
        
        std::cout << "Фильм успешно отредактирован!\n";
    } catch (const FilmNotFoundException& e) {
        std::cout << "Фильм с ID " << id << " не найден.\n";
    }
}

const Film* FilmArray::getAllFilms() const {
    return films;
}

int FilmArray::getNextId() const {
    if (isEmpty()) return 1;
    int maxId = films[0].getId();
    for (int i = 1; i < size; i++) {
        if (films[i].getId() > maxId) {
            maxId = films[i].getId();
        }
    }
    return maxId + 1;
}
