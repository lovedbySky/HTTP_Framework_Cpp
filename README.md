# Simple HTTP Framework

Simple HTTP lib for C++ web projects


# Импорт библиотеки
<div class="cpp"><code>#include "http_framework.cpp"</code></div>

# Создание экземпляра класса
<div class="cpp"><code>HttpServer WebApp;</code></div>

# Настройка приложения

   <code>
      WebApp.Config.secret_key = "12345";
      WebApp.Config.project_path = "project/";
   </code>


# Запуск приложения

   <code>
      <p>WebApp.run("127.0.0.1", 8080, true);</p>
      <p class="comment">// Первый аргумент функции принимает IP адресс</p>
      <p class="comment">// Второй аргумент функции принимает порт</p>
      <p class="comment">// Третий аргумент функции включает/выключает debug mode</p>
   </code>

