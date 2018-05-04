cmake_minimum_required(VERSION 3.10)
project(SmartFridge_ITPS_Ianne_Carbonara_Buonamico C)

set(CMAKE_C_STANDARD 99)

add_executable(SmartFridge_ITPS_Ianne_Carbonara_Buonamico main.c account.h account.c passwd.h passwd.c file.c file.h mainmenu.c mainmenu.h funzioni_switch.c funzioni_switch.h)