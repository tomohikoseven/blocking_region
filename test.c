#include <stdio.h>
#include "ruby.h"
#include "ruby/intern.h"
#include <pthread.h>

pthread_mutex_t _lock = PTHREAD_MUTEX_INITIALIZER;

int
fib( int n, char ch )
{
    printf("thread:%c\n", ch );
    if( n < 0 )     return -1;
    if( n == 0 )    return 1;
    if( n == 1 )    return 1;
    if( n > 1 )     return fib( n - 1, ch ) + fib( n - 2, ch );

    return -1;
}

void*
do_thread( char c )
{
    printf( "fib start\n" );
    rb_thread_blocking_region(pthread_mutex_lock, (void*)&_lock, RUBY_UBF_IO, NULL );
    fib( 6, c);
    pthread_mutex_unlock( &_lock );
    printf( "fib end\n" );
}
void
Init_test1()
{
    pthread_t sub;
    int ret;
    int fibarg = 20;
    char aa = 'a';
    char bb = 'b';
    //pthread_mutex_init( &sub, NULL );

    printf( "get mutex\n" );
    pthread_mutex_lock( &_lock );

    ret = pthread_create( &sub, NULL, do_thread, &bb ); 
    fib( 5, aa );
    pthread_mutex_unlock( &_lock );

}
