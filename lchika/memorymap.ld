MEMORY
{
	flash : ORIGIN = 0x20000000, LENGTH = 0x8000
}
SECTIONS
{
	.text:
	{
		*(.text*)
	} > flash
}

