import time
import threading

# Многопоточная функция с потоками для подсчета количества слов, поиска самого длинного слова и частоты символов
def multi_threaded_version_3(file_path):
    # Функция для нахождения самого длинного слова
    def find_longest_word(words, result):
        longest_word = ""
        for word in words:
            if len(word) > len(longest_word):
                longest_word = word
        result["longest_word"] = longest_word

    # Функция для подсчета количества слов
    def count_words(words, result):
        result["word_count"] = len(words)

    # Функция для подсчета частоты символов в самом длинном слове
    def count_letter_frequency(result):
        longest_word = result.get("longest_word", "")
        letter_frequency = {}
        for letter in longest_word:
            if letter in letter_frequency:
                letter_frequency[letter] += 1
            else:
                letter_frequency[letter] = 1
        result["letter_frequency"] = letter_frequency

    # Начало замера времени
    start_time = time.time()

    # Чтение данных из файла с явной кодировкой cp1251
    with open(file_path, 'r', encoding='cp1251') as file:
        words = [line.strip() for line in file]

    # Словарь для хранения результатов из потоков
    result = {}

    # Создание потоков для выполнения разных задач
    thread1 = threading.Thread(target=find_longest_word, args=(words, result))
    thread2 = threading.Thread(target=count_words, args=(words, result))

    # Запуск первых двух потоков
    thread1.start()
    thread2.start()

    # Ожидание завершения потока с поиском самого длинного слова, чтобы можно было использовать его результат
    thread1.join()

    # Создаем и запускаем третий поток для подсчета частоты символов в самом длинном слове
    thread3 = threading.Thread(target=count_letter_frequency, args=(result,))
    thread3.start()

    # Ожидание завершения всех потоков
    thread2.join()
    thread3.join()

    # Конец замера времени
    end_time = time.time()
        # Вывод результатов
    print(f"Самое длинное слово: {result['longest_word']}")
    print(f"Количество слов: {result['word_count']}")
    print("Частота букв в самом длинном слове:")
    for letter, freq in result['letter_frequency'].items():
        print(f"{letter}: {freq}")

    # Подсчет и вывод времени выполнения
    execution_time4 = end_time - start_time
 
    return(execution_time4)
