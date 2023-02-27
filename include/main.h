
struct thread_args {
    unsigned long long thread_num;
    unsigned long long thread_total;
    unsigned long long rad;
    unsigned long long* point_array;
};

unsigned long long circle_points(unsigned long long rad);

unsigned long long square_points(unsigned long long rad);

double compare(unsigned long long rad);

void pseudo_thread_process(unsigned long long* output, unsigned long long total_threads, unsigned long long num_thread, unsigned long long rad);

void thread_process(thread_args* args_array);

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
