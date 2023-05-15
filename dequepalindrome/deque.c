#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef char element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} queuetype;

void init_queue(queuetype* q) {
    q->front = q->rear = 0;
}

int is_empty(queuetype* q) {
    return (q->front == q->rear);
}

int is_full(queuetype* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(queuetype* q, element item) {
    if (is_full(q)) {
        fprintf(stderr, "Queue is Full\n");
    }
    else {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->data[q->rear] = item;
    }
}

element dequeue(queuetype* q) {
    if (is_empty(q)) {
        fprintf(stderr, "Queue is Empty\n");
        return '\0';
    }
    else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        return (q->data[q->front]);
    }
}

bool is_palindrome(queuetype* q) {
    int start = (q->front + 1) % MAX_QUEUE_SIZE;
    int tail = q->rear;

    while (start != tail && (tail + 1) % MAX_QUEUE_SIZE != start) {
        if (q->data[start] != q->data[tail]) {
            return false;
        }
        start = (start + 1) % MAX_QUEUE_SIZE;
        tail = (tail - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    }
    return true;
}

int main() {
    char input_string[MAX_QUEUE_SIZE];
    queuetype q;

    while (1) {
        init_queue(&q);
        printf("Enter a string(or input exit) : ");
        scanf_s(" %[^\n]", input_string, 100);

        if (strcmp(input_string, "exit") == 0) {
            break;
        }

        int len = strlen(input_string);
        for (int i = 0; i < len; i++) {
            char ch = tolower(input_string[i]);
            if (isalpha(ch)) {
                enqueue(&q, ch);
            }
        }

        if (is_palindrome(&q)) {
            printf("%s is a palindrome.\n", input_string);
        }
        else {
            printf("%s is not a palindrome.\n", input_string);
        }
    }
    return 0;
}