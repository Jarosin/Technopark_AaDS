/*
Задача 1. Хеш-таблица (6 баллов)
Обязательная задача
Реализуйте структуру данных типа “множество строк” на основе динамической
хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из
строчных латинских букв. Хеш-функция строки должна быть реализована с помощью
вычисления значения многочлена методом Горнера. Начальный размер таблицы должен
быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4. Структура данных должна
поддерживать операции добавления строки в множество, удаления строки из
множества и проверки принадлежности данной строки множеству.

1_2. Для разрешения коллизий используйте двойное хеширование.

Требования: В таблице запрещено хранение указателей на описатель элемента.
Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись
операции состоит из типа операции и следующей за ним через пробел строки, над
которой проводится операция. Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество;
    -  означает удаление  строки из множества;
    ?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом
множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он
присутствует в этом множестве. Формат выходных данных Программа должна вывести
для каждой операции одну из двух строк OK или FAIL, в зависимости от того,
встречается ли данное слово в нашем множестве.

*/

#include <iostream>
#include <vector>

constexpr auto kDeleteValue = "DELETE";
constexpr auto kNullValue = "NULL";
constexpr size_t kDefaultMul = 73;
constexpr size_t kDefaultMulSecondary = 103;

class Hasher {
 public:
  Hasher(size_t mul = kDefaultMul) : mul(mul) {}
  size_t operator()(const std::string& key) {
    size_t res = 0;
    for (const auto& elm : key) {
      res = res * mul + elm;
    }
    return res;
  }

 private:
  size_t mul;
};

template <typename Hasher>
class HashTable {
 public:
  HashTable(Hasher hash, size_t initial_size = 8)
      : hash_primary(hash),
        hash_secondary(kDefaultMulSecondary),
        count(0),
        table(initial_size, kNullValue) {}
  bool Has(const std::string& key) {
    size_t secondary_hash_value = 2 * hash_secondary(key) + 1;
    size_t primary_hash_value = hash_primary(key);
    size_t hash_value = primary_hash_value % table.size();
    size_t looked_count = 0;
    while (looked_count < table.size()) {
      if (table[hash_value] == kNullValue) return false;
      if (table[hash_value] == key) {
        return true;
      }
      looked_count++;
      hash_value = (primary_hash_value + secondary_hash_value * looked_count) %
                   table.size();
    }
    return false;
  }
  bool Add(const std::string& key) {
    size_t secondary_hash_value = 2 * hash_secondary(key) + 1;
    size_t primary_hash_value = hash_primary(key);
    size_t hash_value = primary_hash_value % table.size();
    size_t looked_count = 0;
    size_t first_delete_index = 0;
    bool met_delete = false;
    while (looked_count < table.size()) {
      if (table[hash_value] == kNullValue) {
        if (met_delete) {
          table[first_delete_index] = key;
        } else {
          table[hash_value] = key;
        }
        count++;
        if (count >= static_cast<int>(0.75 * table.size())) grow();
        return true;
      }
      if (table[hash_value] == key) {
        return false;
      }
      if (!met_delete && table[hash_value] == kDeleteValue) {
        met_delete = true;
        first_delete_index = hash_value;
      }
      looked_count++;
      hash_value = (primary_hash_value + secondary_hash_value * looked_count) %
                   table.size();
    }
    if (met_delete) {
      table[first_delete_index] = key;
      count++;
      if (count >= static_cast<int>(0.75 * table.size())) grow();
      return true;
    }
    return false;
  }
  bool Delete(const std::string& key) {
    size_t secondary_hash_value = 2 * hash_secondary(key) + 1;
    size_t primary_hash_value = hash_primary(key);
    size_t hash_value = primary_hash_value % table.size();
    size_t looked_count = 0;
    while (looked_count < table.size()) {
      if (table[hash_value] == kNullValue) return false;
      if (table[hash_value] == key) {
        table[hash_value] = kDeleteValue;
        count--;
        return true;
      }
      looked_count++;
      hash_value = (primary_hash_value + secondary_hash_value * looked_count) %
                   table.size();
    }
    return false;
  }

 private:
  size_t count;
  std::vector<std::string> table;
  Hasher hash_primary, hash_secondary;
  void grow() {
    std::vector<std::string> new_table(table.size() * 2, kNullValue);
    for (const auto& key : table) {
      if (key == kNullValue || key == kDeleteValue) continue;

      size_t primary_hash_value = hash_primary(key);
      size_t secondary_hash_value = 2 * hash_secondary(key) + 1;
      size_t looked_count = 0;
      size_t hash_value = primary_hash_value % new_table.size();
      while (looked_count < new_table.size()) {
        if (new_table[hash_value] == kNullValue) {
          new_table[hash_value] = key;
          break;
        }
        looked_count++;
        hash_value =
            (primary_hash_value + secondary_hash_value * looked_count) %
            new_table.size();
      }
    }
    table = std::move(new_table);
  }
};

int main() {
  Hasher hasher(kDefaultMul);
  HashTable<Hasher> hash_table(hasher);
  std::string key;
  char sign;
  while (std::cin >> sign >> key) {
    switch (sign) {
      case '+':
        std::cout << (hash_table.Add(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '?':
        std::cout << (hash_table.Has(key) ? "OK" : "FAIL") << std::endl;
        break;
      case '-':
        std::cout << (hash_table.Delete(key) ? "OK" : "FAIL") << std::endl;
        break;
      default:
        return 0;
    }
  }
  return 0;
}
