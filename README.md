# Simple HTTP Framework

Simple HTTP lib for C++ web projects


# Импорт библиотеки
      #include "http_framework.cpp"

# Создание экземпляра класса
      HttpServer WebApp;

# Настройка приложения
      WebApp.Config.secret_key = "12345";
      WebApp.Config.project_path = "project/";


# Запуск приложения
      WebApp.run("127.0.0.1", 8080, true);
      // Первый аргумент функции принимает IP адресс
      // Второй аргумент функции принимает порт
      // Третий аргумент функции включает/выключает debug mode


