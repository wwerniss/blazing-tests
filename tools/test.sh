#!/bin/bash

# Выход при ошибке
set -e

# Очистка и создание директории сборки
echo "🧹 Очистка директории сборки..."
rm -rf build
mkdir -p build
cd build

# Конфигурация CMake
echo "⚙️  Конфигурация CMake..."
cmake ..

# Сборка проекта
echo "🔨 Сборка проекта..."
# Используем sysctl для macOS вместо nproc
make -j$(sysctl -n hw.ncpu)

# Запуск тестов
echo "🚀 Запуск тестов..."
./common_tests

echo "✅ Тестирование завершено!"
ctest --output-on-failure --verbose