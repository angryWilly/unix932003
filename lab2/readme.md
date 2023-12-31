# Lab2 Настройка Docker

В этом руководстве приведена инструкция по сборке и запуску контейнера Docker с помощью Docker Compose.

## Необходимые условия

- Docker и Docker Compose установлены на вашей машине.

## Шаги для выполнения

1. Откройте терминал/консоль в каталоге проекта.

2. Соберите образы Docker:
    ```bash
    docker-compose build --no-cache
    ```

3. Запустите контейнеры Docker с масштабированием:
    ```bash
    docker-compose up --scale concurrent_container=10
    ```
    Примечание: Настройте коэффициент масштабирования по мере необходимости (например, `--scale concurrent_container=1` или `--scale concurrent_container=50`).

4. Чтобы остановить запущенные контейнеры, нажмите `Ctrl + C` в терминале и дождитесь их остановки.

5. При необходимости удалите контейнеры и связанные с ними тома:
    ```bash
    docker-compose down -v
    ```
   Это очистит все оставшиеся файлы, не удаленные скриптами.

Теперь вы можете повторить шаги 2-4, если это необходимо для вашей среды разработки или тестирования.
