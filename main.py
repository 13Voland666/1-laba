from single import single_threaded_version

from multi import multi_threaded_version_3
# Вызов функций

file_path = 'data.txt'
print("Однопоточная версия:")

a=single_threaded_version(file_path)
print("\nМногопоточная версия:")

d=multi_threaded_version_3(file_path)
print (f'Время действия алгоритмов:\nОднопоточная:  {a} сек.\nМногопоточная: {d} сек.')