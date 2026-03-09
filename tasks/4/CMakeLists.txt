add_executable(05.05 05.05.cpp)
add_subdirectory(06.05)
add_executable(07.01 07.01.cpp)
add_executable(07.02 07.02.cpp)
add_executable(07.03 07.03.cpp)
add_subdirectory(07.04)
add_subdirectory(07.05)
add_executable(08.01 08.01.cpp)
add_subdirectory(08.02)
add_executable(08.03 08.03.cpp)
add_executable(08.04 08.04.cpp)
add_executable(08.05 08.05.cpp)

# Я не хочу выполнять 06.04. У меня сейчас в системе довольно хрупкий конфиг (Ubuntu 22.04, Clang 18 из-за модулей, конфликты Boost с libc++), и лишний раз ломать окружение глобальными установками не хочется. В самом проекте я уже подключил все библиотеки через vcpkg — это и чище, и профессиональнее. Сделать через виртуалку Multipass мне не проблема, если это принципиально для оценки, но, честно говоря, это кажется лишней тратой времени и нервов
