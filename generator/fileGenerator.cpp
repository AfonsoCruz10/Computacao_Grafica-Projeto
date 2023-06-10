#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "include/Plane.hpp"
#include "include/Box.hpp"
#include "include/Sphere.hpp"
#include "include/Cone.hpp"
#include "include/Bezier.hpp"
#include "include/Torus.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	// Create and open a text file
	string path = argv[argc - 1];
	string gn = "GeneratedFiles/";
	char *shape = argv[1];

	// Criar triangulos para shape
	if (strcmp(shape, "plane") == 0)
	{
		if (argc != 5)
		{
			cout << "Numero de argumentos invalidos para " << shape;
			return 0;
		}
		Plane p;
		p.generate(stoi(argv[2]), stoi(argv[3]));

		path = gn + path;
		p.serialize(path);
	}
	else if (strcmp(shape, "sphere") == 0)
	{
		if (argc != 6)
		{
			cout << "Numero de argumentos invalidos para " << shape;
			return 0;
		}
		Sphere p;
		p.generate(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

		path = gn + path;
		p.serialize(path);
	}
	else if (strcmp(shape, "box") == 0)
	{
		if (argc != 5)
		{
			cout << "Numero de argumentos invalidos para " << shape;
			return 0;
		}
		Box p;
		p.generate(stoi(argv[2]), stoi(argv[3]));

		path = gn + path;
		p.serialize(path);
	}
	else if (strcmp(shape, "cone") == 0)
	{
		if (argc != 7)
		{
			cout << "Numero de argumentos invalidos para " << shape;
			return 0;
		}
		Cone p;
		p.generate(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

		path = gn + path;
		p.serialize(path);
	}

	else if (strcmp(argv[1], "patch") == 0)
	{
		if (argc - 2 != 3)
		{
			printf("Invalid number of arguments for patch: %d.\n", argc - 2);
			exit(0);
		}

		char *input_file = (char *)malloc(sizeof(char) * (strlen(argv[2])));
		strcpy(input_file, argv[2]);

		int tessellation = strtol(argv[3], NULL, 10);

		if (tessellation < 0)
		{
			printf("Invalid argument for tessellation: %d.\n", tessellation);
			exit(0);
		}

		Bezier b;

		b.parseBezier(input_file);
		b.bezierPoints(tessellation);

		path = gn + path;
		b.serialize(path);
	}
	else if (strcmp(argv[1], "torus") == 0)
	{
		if (argc - 2 != 5)
		{
			printf("Invalid number of arguments for torus: %d.\n", argc - 2);
			exit(0);
		}

		float inRadius = strtof(argv[2], NULL);
		float outRadius = strtof(argv[3], NULL);
		int slices = strtol(argv[4], NULL, 10);
		int layers = strtol(argv[5], NULL, 10);

		if (inRadius < 0)
		{
			printf("Invalid argument for radius: %f.\n", inRadius);
			exit(0);
		}

		if (outRadius < 0)
		{
			printf("Invalid argument for height: %f.\n", outRadius);
			exit(0);
		}

		if (slices < 0)
		{
			printf("Invalid argument for slices: %d.\n", slices);
			exit(0);
		}

		if (layers < 0)
		{
			printf("Invalid argument for stacks: %d.\n", layers);
			exit(0);
		}

		Torus t;

		t.generate(inRadius, outRadius, slices, layers);

		path = gn + path;
		t.serialize(path);
	}

	return 1;
};