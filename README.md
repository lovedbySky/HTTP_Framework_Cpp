# Simple HTTP Framework

Simple HTTP lib for C++ web projects


# Импорт библиотеки
<code>#include "http_framework.cpp"</code>

# Создание экземпляра класса
<code>HttpServer WebApp;</code>

# Настройка приложения

   <code>
      WebApp.Config.secret_key = "12345";
      WebApp.Config.project_path = "project/";
   </code>


# Запуск приложения

   <code>
      WebApp.run("127.0.0.1", 8080, true);
      // Первый аргумент функции принимает IP адресс
      // Второй аргумент функции принимает порт
      // Третий аргумент функции включает/выключает debug mode
   </code>

