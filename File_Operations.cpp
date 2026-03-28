#include "File_Operations.h"
#include <fstream>
#include <iostream>

void FileOperations::saveToFile(const std::string& filename, const FilmArray& array) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Ошибка: не удалось открыть файл для записи!\n";
        return;
    }
    
    const Film* films = array.getAllFilms();
    int size = array.getSize();
    
    // Записываем количество фильмов
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // Записываем каждый фильм
    for (int i = 0; i < size; i++) {
        const Film& film = films[i];
        
        // Сохраняем ID
        int id = film.getId();
        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        
        // Сохраняем строки с длиной
        std::string title = film.getTitle();
        int titleLen = title.length();
        file.write(reinterpret_cast<const char*>(&titleLen), sizeof(titleLen));
        file.write(title.c_str(), titleLen);
        
        std::string genre = film.getGenre();
        int genreLen = genre.length();
        file.write(reinterpret_cast<const char*>(&genreLen), sizeof(genreLen));
        file.write(genre.c_str(), genreLen);
        
        // Сохраняем числа
        int duration = film.getDuration();
        file.write(reinterpret_cast<const char*>(&duration), sizeof(duration));
        
        double rating = film.getRating();
        file.write(reinterpret_cast<const char*>(&rating), sizeof(rating));
        
        int year = film.getYear();
        file.write(reinterpret_cast<const char*>(&year), sizeof(year));
    }
    
    file.close();
    std::cout << "Данные успешно сохранены в файл '" << filename << "'\n";
}

FilmArray FileOperations::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    FilmArray array;
    
    if (!file) {
        std::cout << "Файл '" << filename << "' не найден. Создана новая база данных.\n";
        return array;
    }
    
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        // Читаем ID
        int id;
        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        
        // Читаем название
        int titleLen;
        file.read(reinterpret_cast<char*>(&titleLen), sizeof(titleLen));
        std::string title(titleLen, '\0');
        file.read(&title[0], titleLen);
        
        // Читаем жанр
        int genreLen;
        file.read(reinterpret_cast<char*>(&genreLen), sizeof(genreLen));
        std::string genre(genreLen, '\0');
        file.read(&genre[0], genreLen);
        
        // Читаем числа
        int duration;
        file.read(reinterpret_cast<char*>(&duration), sizeof(duration));
        
        double rating;
        file.read(reinterpret_cast<char*>(&rating), sizeof(rating));
        
        int year;
        file.read(reinterpret_cast<char*>(&year), sizeof(year));
        
        // Создаем и добавляем фильм
        Film film(id, title, genre, duration, rating, year);
        array.addFilm(film);
    }
    
    file.close();
    std::cout << "Загружено " << array.getSize() << " фильмов из файла '" << filename << "'\n";
    
    return array;
}
