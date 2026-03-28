#include "FilmArray.h"
#include "File_Operations.h"
#include <iostream>
#include <limits>

void printMenu() {
    std::cout << "\n=== Управление базой данных кинотеатра ===\n";
    std::cout << "1. Вывести все фильмы\n";
    std::cout << "2. Найти фильмы\n";
    std::cout << "3. Добавить новый фильм\n";
    std::cout << "4. Удалить фильм\n";
    std::cout << "5. Редактировать фильм\n";
    std::cout << "6. Сохранить изменения в файл\n";
    std::cout << "0. Выйти из программы\n";
    std::cout << "Выберите действие: ";
}

void searchMenu(FilmArray& films) {
    if (films.isEmpty()) {
        std::cout << "База данных пуста.\n";
        return;
    }
    
    std::cout << "\n=== Поиск фильмов ===\n";
    std::cout << "1. По жанру\n";
    std::cout << "2. По рейтингу (выше указанного)\n";
    std::cout << "3. По году выпуска\n";
    std::cout << "Выберите критерий поиска: ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (choice) {
        case 1: {
            std::string genre;
            std::cout << "Введите жанр для поиска: ";
            std::getline(std::cin, genre);
            films.searchByGenre(genre);
            break;
        }
        case 2: {
            double minRating;
            std::cout << "Введите минимальный рейтинг: ";
            std::cin >> minRating;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            films.searchByRating(minRating);
            break;
        }
        case 3: {
            int year;
            std::cout << "Введите год выпуска: ";
            std::cin >> year;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            films.searchByYear(year);
            break;
        }
        default:
            std::cout << "Неверный выбор.\n";
    }
}

int main(int argc, char* argv[]) {
    // Определяем имя файла базы данных
    std::string filename = "cinema_database.bin";
    if (argc > 1) {
        filename = argv[1];
        std::cout << "Используется файл базы данных: " << filename << "\n";
    } else {
        std::cout << "Используется файл базы данных по умолчанию: " << filename << "\n";
        std::cout << "Для использования другого файла запустите программу с параметром:\n";
        std::cout << "  " << argv[0] << " <имя_файла>\n\n";
    }
    
    // Загрузка данных
    FilmArray films = FileOperations::loadFromFile(filename);
    
    int choice;
    
    do {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                films.displayAll();
                break;
                
            case 2:
                searchMenu(films);
                break;
                
            case 3: {
                Film newFilm;
                newFilm.setId(films.getNextId());
                newFilm.input();
                films.addFilm(newFilm);
                FileOperations::saveToFile(filename, films);
                break;
            }
                
            case 4: {
                int id;
                std::cout << "Введите ID фильма для удаления: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                films.removeFilm(id);
                FileOperations::saveToFile(filename, films);
                break;
            }
                
            case 5: {
                int id;
                std::cout << "Введите ID фильма для редактирования: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                films.editFilm(id);
                FileOperations::saveToFile(filename, films);
                break;
            }
                
            case 6:
                FileOperations::saveToFile(filename, films);
                break;
                
            case 0:
                std::cout << "Выход из программы...\n";
                break;
                
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
        
    } while (choice != 0);
    
    // Финальное сохранение
    FileOperations::saveToFile(filename, films);
    
    return 0;
}
