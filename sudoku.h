struct box
{
	int value;
	_Bool preset;
	struct box *up;
	struct box *left;
	struct box *right;
	struct box *down;
};

typedef struct box Box;

Box *box_construct(int value, Box *left,Box *right,Box *up,Box *down);
Box *grid_construct(void);
void destroy_grid(Box *head);
void add_preset(int n,int pos,Box *head);
_Bool is_row(int n,Box *head);
_Bool is_column(int n,Box *head);
int box_pos(Box *head);
_Bool is_box(int n,Box *head,int pos);
_Bool is_valid(int n,Box *head);
_Bool is_end_row(Box *head);
_Bool is_end_column(Box *head);
void solve(Box *head,int *count,Box *top);
void print_grid(Box *head);
