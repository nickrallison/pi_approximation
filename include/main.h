
struct thread_args {
    long long thread_num;
    long long thread_total;
    long long rad;
    long long* point_array;
};

long long circle_points(long long rad);

long long square_points(long long rad);

double compare(long long rad);

void pseudo_thread_process(long long* output, long long total_threads, long long num_thread, long long rad);

void thread_process(thread_args* args_array);

long long circle_points_digamma(long long rad);

/*

int main()
{
    int* points = new int[N];
    pthread_t my_thread[N];

    long id;
    for(id = 1; id <= N; id++) {
            int ret =  pthread_create(&my_thread[id], NULL, &worker_thread, (void*)id);
            if(ret != 0) {
                    printf("Error: pthread_create() failed\n");
                    exit(EXIT_FAILURE);
            }
    }

    pthread_exit(NULL);
}*/
