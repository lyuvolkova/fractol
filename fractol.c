#include "fractol.h"
void input_data_help()
{
    printf("\nIt is necessary to select the input parameter\n");
    printf("from the following:\n" );
    printf("   *Julia\n");
    printf("   *Mandelbrot\n");

}
int type_fractol(char* name_fractol)
{
    int i;

    i = 0;
    if(ft_strcmp("Julia", name_fractol))
        i = 1;
    else if(ft_strcmp("Mandelbrot", name_fractol))
        i = 2;
    return(i);

}

int main(int argc, char** argv)
{
    int i;

    i = 1;
    if(argc < 2)
    {
       input_data_help();
       return(0);
    }
    while(i < argc)
    {
        if(!type_fractol(argv[i]))
            return(1);
        printf("%d\n",type_fractol(argv[i]));
        i++;
    }
    void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
       
    return(0);

}