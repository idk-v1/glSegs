#include "objReader.h"

gls_Stack obj_readVerts(const char* filename)
{
	gls_Stack verts;
	gls_Stack outVerts;
	FILE* file = fopen(filename, "r");
	if (!file)
	{
		stack_init(&outVerts, sizeof(gls_Vec3f), 0);
		return outVerts;
	}

	char buf[200];
	stack_init(&verts, sizeof(gls_Vec3f), 1000);
	stack_init(&outVerts, sizeof(gls_Vec3f), 1000);

	int count = 0;
	while (fgets(buf, 200, file))
	{
		if (buf[1] == ' ')
		{
			if (buf[0] == 'v')
			{
				gls_Vec3f vec = { 0 };
				char* end = &buf[1];
				vec.x = strtof(end, &end);
				vec.y = strtof(end, &end);
				vec.z = strtof(end, &end);

				stack_push(&verts, &vec);
			}
			else if (buf[0] == 'f')
			{
				size_t x = 0, y = 0, z = 0;
				char* end = &buf[1];
				x = strtoull(end, &end, 10) - 1;
				if (*end == '/')
					while (*(end++) != ' ');
				y = strtoull(end, &end, 10) - 1;
				if (*end == '/')
					while (*(end++) != ' ');
				z = strtoull(end, &end, 10) - 1;

				stack_push(&outVerts, stack_index(&verts, x));
				stack_push(&outVerts, stack_index(&verts, y));
				stack_push(&outVerts, stack_index(&verts, z));
			}
		}

		count++;
	}

	fclose(file);

	stack_free(&verts);
	return outVerts;
}
