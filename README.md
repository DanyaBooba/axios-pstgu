# Аксиос

Программа для сбора информации о выполненных заданий студентами.

## Выполняет

- сохранение названий;
- сохранение имени студента и сданных заданий;
- проверка на допуск и наличие трудностей.

## Работа с программой

Для выполнение программы используйте команду:

`./tasks`

Если не передать параметры или допустить в них ошибку (неверное имя файла или ошибка в параметрах), будет отображено диалогое окно, которое подскажет, как правильно работать с программой.

### Возможности

- Можно указать флаг `-p`, чтобы задать верхнюю планку для сдачи без проблем (по умолчанию 80%):

`./tasks -p 80`

- Дополнительно можно передавать имена файлов:

`./tasks <filename1> <filename2> ... <filename>`

- В одном файле может быть несколько таблиц и другой текст.

## Пример таблицы

|           | задание 1 | задание 2 | задание 3 |
| --------- | --------- | --------- | --------- |
| студент 1 | +         | +         | -         |
| @ @ @     |           |           |           |
| студент 2 |           | +         | +         |

## Требуется добавить в программу

- получение данных с сервера.
