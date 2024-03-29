# Lab1_3rdPart
Fundamentals algorithms, MAI FIIT 2021

## Task1
  Реализуйте функцию с переменным числом аргументов,
принимающую в качестве входных параметров указатель на
функцию для поиска подстроки в строке, строку substr и пути к
файлам. Функция должна вернуть коллекцию имён файлов, в
которых найдено хотя бы одно вхождение подстроки substr. Поиск
подстроки в строке реализуйте самостоятельно в виде функции.
Организуйте наглядный вывод результатов.

## Task2
  Реализуйте функцию с переменным числом аргументов,
принимающую на вход количество и координаты точек (в виде
объектов структур) многоугольника и вычисляющую, является ли
этот многоугольник выпуклым.

## Task3
  Реализуйте функцию с переменным числом аргументов, находящую
значения многочлена степени 𝑛 в заданной точке. Аргументами
функции являются точка, в которой определяется значение
многочлена, степень многочлена, его коэффициенты.

## Task4
  В текстовом файле находятся числа, записанные в разных системах
счисления, при этом информация о конкретной системе счисления
для каждого числа утеряна. В файле числа разделены произвольным
количеством разделителей (символы пробела, табуляции, переноса
строки). Реализуйте приложение, которое для каждого числа из
входного файла (путь к файлу - аргумент командной строки)
определяет минимальную систему счисления, в которой
представление этого числа корректно и в выходной файл выводит
число, определенную для него систему счисления и представление
этого числа в системе счисления с основанием 10.

 ## Task5
  Реализуйте функцию с переменным числом аргументов,
вычисляющую сумму переданных чисел в заданной системе
счисления. Десятичное представление чисел может не поместиться в
типы int, long int и т. д. (для решения возникшей проблемы напишите
функцию «сложения в столбик» чисел в заданной системе
счисления). Запись числа, получившегося в результате, не должна
содержать ведущие нули.

## Task6
  На вход программе через аргументы командной строки подаётся
путь к текстовому файлу, содержащему последовательность строк, в
каждой из которых записаны один или несколько операторов над
булевскими векторами из множества [A, B, …, Z] и, возможно,
однострочные или многострочные комментарии. Символ % является
открывающим однострочный комментарий; символы { и } являются
открывающим и закрывающим многострочный комментарий
соответственно (приоритет имеет комментарий, начинающийся
раньше).
Возможный вид операторов:
1) A := B <op> C; где <op> - логическая операция из списка:
* + (дизъюнкция);
* & (конъюнкция);
* -> (импликация);
* <- (обратная импликация);
* ~ (эквиваленция);
* <> (сложение по модулю 2);
* +> (коимпликация);
* ? (штрих Шеффера);
* ! (функция Вебба, стрелка Пирса);
* := - оператор присваивания.
2) X := \W; - логическое отрицание.
3) read(D, base); - ввод значения в переменную D в системе
счисления с основанием base (в диапазоне [2..36]).
4) write(Q, base); - вывод значения из переменной Q в системе
счисления с основанием base (в диапазоне [2..36]).
Разделителем между операторами является символ “;”. Пробелы,
символы табуляций и переносы строк могут присутствовать
произвольно, различий между заглавными и строчными буквами нет,
вложенные комментарии допускаются, уровень вложенности
произвольный. При наличии в командной строке флага /trace,
следующим аргументом командной строки указывается путь к файлу
трассировки (необходимо выводить в файл подробную информацию
о выполнении каждой инструкции из файла - порядковый номер
инструкции, над какими переменными выполняется, результат
выполнения). Напишите программу-интерпретатор инструкций в
заданном файле. Необходимо предусмотреть обработку
всевозможных ошибок. Интерпретатор чувствителен к регистру.
Конвертации чисел между различными системами счисления
реализовать при помощи схемы Горнера и обратной ей. Запрещается
буферизованный ввод из файла - чтение файла посимвольное.

## Task7
  Разработайте программу для организации макрозамен в тексте. На
вход программы подается текстовый файл, который содержит в
начале файла набор директив #define и далее обычный текст.
Синтаксис директивы соответствует стандарту языка C:

> #define <def_name> <def_value>
    
Директивы не параметризуются. Ваша программа должна
обработать и перезаписать текстовый файл, выполнив замены во
всем тексте последовательности символов <def_name> на
<def_value>. Количество директив произвольно, некорректных
директив нет, размер текста произволен. <def_name> -
последовательность символов, допускающая использование
символов латинского алфавита (прописные и заглавные буквы не
отождествляются) и символов цифр; <def_value> является
произвольной последовательностью символов (завершается
переносом строки). Для хранения имен макросов и
макроподстановок используйте хеш-таблицу фиксированного
размера HASHSIZE (определите величину этой константы равной
128). Для вычисления хеш-функции интерпретируйте <def_name>
как число, записанное в системе счисления с основанием 62
(алфавит этой системы счисления состоит из символов {0, …, 9, A,
…, Z, a, …, z}). Переведите это число в систему счисления с
основанием 10 и возьмите остаток от деления на HASHSIZE,
полученное значение и будет являться хеш-значением,
соответствующим <def_name>. Для разрешения коллизий
используйте метод открытого хэширования (цепочек).

## Task8

  Разработайте интерпретатор с настраиваемым синтаксисом. Для
настройки интерпретатора через аргументы командной строки
подается файл с описанием синтаксиса операций. Файл настроек
содержит сопоставления реальных операций (слева), которые может
выполнить интерпретатор и их псевдонимов (справа), которые будут
использованы в программах, которые будут поданы на вход
(определение псевдонимов необязательно). Файл настроек может
содержать однострочные комментарии, которые начинаются с
символа #. Также в файле настроек можно сконфигурировать
порядок следования операндов и операций (по умолчанию: операция
предшествует списку операндов, переменная находится слева от
операции присваивания).


Примерный файл настроек выглядит следующим образом:
```c++ 
left= #означает, что результат сохраняется в переменную, которая
стоит слева от присваивания: result <-> sum(op1, op2);
  #может быть написано right=, соответствующий синтаксис:
sum(op1, op2) <-> result.
op() #означает, что операция предшествует списку аргументов:
sum(op1, op2); in(op1);
  #может быть написано ()op, то есть операция находится
после списка аргументов: (op1, op2)sum; (op1)out;
  #может быть написано (op)() или ()(op), то есть для
бинарных операций операция находится между аргументами: sum1
op sum2, а для унарных - в зависимости от расположения скобок
без содержимого по аналогии с первыми двумя случаями.
add sum # переопределение оператора сложения
mult prod # переопределение оператора умножения
sub minus # переопределение оператора вычитания
pow ^ # переопределение оператора возведения в степень
div / # переопределение оператора целочисленного деления
rem % # переопределение оператора взятия по модулю
xor <> # переопределение оператора сложения по модулю 2
input in # переопределение оператора ввода
output print # переопределение оператора вывода
= <-> # переопределение оператора присваивания/инициализации
```
Пример файла настроек для интерпретатора
Интерпретатор оперирует 32-х разрядными целочисленными
переменными, имена которых могут содержать более одного символа
(имена переменных могут содержать символы букв, цифр и символа
подчеркивания ‘_’, не могут начинаться с символа цифры и имеют
максимальную длину 32 символа). Объявление переменных не
требуется, по умолчанию значение переменной равно 0. В качестве
операндов могут выступать целочисленные константы
(начинающиеся с символа - или символа цифры).
Список команд, которые могут быть выполнены интерпретатором:
* add (сложение);
* mult (умножение);
* sub (вычитание);
* pow (возведение в степень),
* div (целочисленное деление),
* rem (взятие по модулю),
* xor (сложение по модулю 2),
* input (ввод значения с клавиатуры),
* output (вывод значения переменной на экран),


= (присваивание значения выражения переменной или ее
инициализация).


Синтаксис инструкций (при настройках по умолчанию) имеет вид:
* A1 = add(B2, C34); - сложение значений, хранящихся в
переменных с именами B2 и C34 и сохранение
результата сложения в переменную с именем A1;
* Bbbb = rem(modpow, 9); - взятие остатка от деления
значения, хранящегося в переменной с именем modpow,
на 9 и сохранение остатка в переменную с именем Bbbb;
* d12 = in(base); - ввод значения в переменную с именем
d12 системе счисления с основанием base (если не
указано, то по умолчанию base = 10);
* print(D, base); - вывод значения из переменной D в
системе счисления с основанием base (если не указано,
то по умолчанию base = 10).


Разделителем между инструкциями является символ “;”. Пробелы,
табуляции и переносы строк могут присутствовать произвольно,
различий между заглавными и строчными буквами нет. Также в
тексте могут присутствовать многострочные комментарии, которые
обрамляются символами [ и ]. При завершении работы
интерпретатор запоминает последний файл настроек, с которым
работал, и при следующем запуске при отсутствии переданного пути
к файлу настроек, настройки интерпретатора должны быть такими
же, как и при последнем запуске. Необходимо предусмотреть
обработку всевозможных ошибок (синтаксиса инструкций и их
выполнения). Интерпретатор чувствителен к регистру. Конвертации
чисел между различными системами счисления реализовать при
помощи схемы Горнера и обратной ей. Запрещается буферизованный
ввод из файла - чтение файла посимвольное.
