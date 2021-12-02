#!/usr/bin/python3
from os import system
from sys import argv
import sys

wrg = argv[1]
cor = argv[2]
gen = argv[3]
if system("g++ -std=c++17 -fsanitize=address -fsanitize=undefined -O2 -o %s %s.cpp" % (wrg, wrg)):
	print("решение не компилируется")
	exit(0)
if system("g++ -std=c++17 -O2 -o %s %s.cpp" % (cor, cor)):
	print("правильное не компилируется")
	exit(0)
if system("g++ -std=c++17 -O2 -o %s %s.cpp" % (gen, gen)):
	print("генератор не компилируется")
while True:
	if system("./%s > te.txt" % gen):
		print("генератор не сработал")
		break
	fte = open("te.txt", "r")
	inp = fte.read().strip()
	fte.close()
	if system("./%s < te.txt > co.txt" % cor):
		print("правильное упало")
		print(inp)
		break
	if system("./%s < te.txt > wr.txt" % wrg):
		print("решение упало")
		print(inp)
		break
	fco = open("co.txt", "r")
	aco = fco.read().strip()
	fco.close()
	fwr = open("wr.txt", "r")
	awr = fwr.read().strip()
	fwr.close()
	if aco != awr:
		print("неправильный ответ")
		print("тест")
		print(inp)
		print("вывело")
		print(awr)
		print("правильно")
		print(aco)
		break
	else:
		print("ок")