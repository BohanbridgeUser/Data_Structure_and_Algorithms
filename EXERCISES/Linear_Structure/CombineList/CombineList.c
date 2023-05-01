List Merge( List L1, List L2 )
{
    if ( !L1 ) return L2;
    else if ( !L2 ) return L1;
    List p=L1, q=L2;
    List L,rear;
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    rear = L;
    while ( p->Next && q->Next ){
        if ( p->Next->Data < q->Next->Data ) {
            rear->Next = p->Next;
            p->Next = p->Next->Next;
            rear = rear->Next;
            rear->Next = NULL;
        } else if ( p->Next->Data > q->Next->Data ) {
            rear->Next = q->Next;
            q->Next = q->Next->Next;
            rear = rear->Next;
            rear->Next = NULL;
        } else if ( p->Next->Data == q->Next->Data ){
            rear->Next = p->Next;
            p->Next = p->Next->Next;
            rear = rear->Next;
            rear->Next = q->Next;
            q->Next = q->Next->Next;
            rear = rear->Next;
            rear->Next = NULL;
        }
    }
    if ( !(p->Next) ){
        rear->Next = q->Next;
        q->Next = NULL;
    } else if ( !(q->Next) ){
        rear->Next = p->Next;
        p->Next = NULL;
    } 
    return L;
}

