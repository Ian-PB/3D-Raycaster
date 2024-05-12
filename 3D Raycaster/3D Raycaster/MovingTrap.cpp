#include "MovingTrap.h"

void MovingTrap::setup(int t_moveType)
{
	direction = t_moveType;
}

void MovingTrap::move(int t_map[], int t_index, int t_type)
{
	int previousIndex = t_index;

	if (timer >= TIME_BETWEEN_MOVES)
	{
		if (direction == 0) // Side to Side
		{
			t_index += 1;
		}

		else if (direction == 1) // Up and Down
		{
			t_index += 8;
		}

		timer = 0;
		
		if (t_map[t_index] == 0)
		{
			t_map[t_index] = t_type; // Set new index
		}
		else
		{
			// Reset
			if (direction == 0)
			{
				t_map[t_index - 6] = t_type;
			}
			if (direction == 1)
			{
				t_map[t_index - 48] = t_type;
			}
		}
		
		if (t_map[previousIndex] == t_type)
		{
			t_map[previousIndex] = 0; // Make previous index empty
		}
	}
	else
	{
		timer++;
	}
}
