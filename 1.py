import pandas as pd
import numpy as np

# Загрузите данные из TXT файла (используйте правильный разделитель и кодировку)
df = pd.read_csv("X:\\Politex\\mnogopotok\\1 laba\\data.txt", sep="\t", encoding="latin1")  # измените sep и encoding при необходимости

# Сохраните оригинальные данные в другой файл
df.to_csv("X:\\Politex\\mnogopotok\\1 laba\\original_data.txt", sep="\t", index=False, encoding="latin1")

# Определите количество строк для удаления (30%)
rows_to_remove = int(len(df) * 0.3)

# Случайно выберите строки для удаления
rows_to_delete = np.random.choice(df.index, size=rows_to_remove, replace=False)

# Удалите выбранные строки
df_dropped = df.drop(rows_to_delete)

# Сохраните обновленный DataFrame в новый TXT файл
df_dropped.to_csv("X:\\Politex\\mnogopotok\\1 laba\\modified_data.txt", sep="\t", index=False, encoding="latin1")

print(f"Удалено {rows_to_remove} строк.")
