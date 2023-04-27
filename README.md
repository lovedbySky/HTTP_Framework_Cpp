# Simple HTTP Framework

Simple HTTP lib for C++ web projects

<div>
            <h2>Импорт библиотеки</h2>
            <div class="cpp"><code>#include "http_framework.cpp"</code></div>

            <h2>Создание экземпляра класса</h2>
            <div class="cpp"><code>HttpServer WebApp;</code></div>

            <h2>Настройка приложения</h2>
            <div class="cpp">
                <code>
                    <p>WebApp.Config.secret_key = "12345";</p>
                    <p>WebApp.Config.project_path = "project/";</p>
                </code>
            </div>

            <h2>Запуск приложения</h2>
            <div class="cpp">
                <code>
                    <p>WebApp.run("127.0.0.1", 8080, true);</p>
                    <p class="comment">// Первый аргумент функции принимает IP адресс</p>
                    <p class="comment">// Второй аргумент функции принимает порт</p>
                    <p class="comment">// Третий аргумент функции включает/выключает debug mode</p>
                </code>
            </div>
        </div>
        
        <div>
            <h2>Пример использования</h2>
            <div class="cpp">
                <code>
                    <p>#include "http_framework.cpp"</p>
                    <p></p>
                    <p>int main()</p>
                    <p>{</p>
                    <p>&nbsp;&nbsp;&nbsp;&nbsp;HttpApplication WebApp;</p>
                    <p>&nbsp;&nbsp;&nbsp;&nbsp;WebApp.Config.secret_key = "12345";</p>
                    <p>&nbsp;&nbsp;&nbsp;&nbsp;WebApp.Config.project_path = "project/";</p>
                    <p>&nbsp;&nbsp;&nbsp;&nbsp;WebApp.run("127.0.0.1", 8080, true);</p>
                    <p>&nbsp;&nbsp;&nbsp;&nbsp;return 0;</p>
                    <p>}</p>
                </code>
            </div>
        </div>
