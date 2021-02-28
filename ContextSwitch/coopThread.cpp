// ----------------------------------------------------------------------------
//
// Context Switch.
//
// Charles Carley 9/8/2020 CSCI-470
//
// ----------------------------------------------------------------------------
#include <memory.h>
#include <cassert>
#include <iostream>

using namespace std;

typedef void (*ThreadFP)(int);

typedef struct pcb_t
{
    uint64_t *rsp;  // 0x00
    uint64_t  rbx;  // 0x08
    uint64_t  rcx;  // 0x10
    uint64_t  rdx;  // 0x18
    uint64_t  rsi;  // 0x20
    uint64_t  rdi;  // 0x28
    uint64_t  rbp;  // 0x30
    uint64_t  rax;  // 0x38
    uint64_t  cst;  // 0x40 current state
} pcb_t;            // 72 bytes

typedef struct thread_t
{
    pcb_t     pcb;  // 0x00 process control block
    uint64_t  tid;  // 0x48 thread id
    uint64_t *stk;  // 0x50 stack
} thread_t;         // 88 bytes


const size_t     MaxStack         = 0xFA00;
const size_t     StackSize        = MaxStack / 8;
static int       ThreadCount      = 0x00;
static thread_t *StaticStorage[2] = {};

extern "C" void ctx_save(pcb_t *, uint64_t);
extern "C" void ctx_load(pcb_t *);
extern "C" void set_stack(uint64_t *, uint64_t);

thread_t *getThread(int id)
{
    if (id >= 0x02)
    {
        assert(0 && "Failed to get thread");
        return nullptr;
    }

    thread_t *obj;
    if (StaticStorage[id] == 0)
    {
        obj = (thread_t *)malloc(sizeof(thread_t));
        memset(obj, 0, sizeof(thread_t));

        obj->tid     = id;
        obj->stk     = (uint64_t *)malloc(MaxStack);

        // Moves the new stack into the RSP.
        obj->pcb.rsp = obj->stk;
        set_stack((uint64_t *)&obj->pcb.rsp, StackSize);

        StaticStorage[id] = obj;
    }
    else
        obj = StaticStorage[id];
    return obj;
}

void startThread(ThreadFP ptr)
{
    if (ThreadCount >= 0x02)
        return;

    thread_t *cctx = getThread(ThreadCount++);
    thread_t *nctx = getThread((cctx->tid + 1) % 0x02);

    // Initially save the switch state here
    // so that  startThread(main2) can be accessed.
    if (nctx->pcb.cst == 0)
        ctx_save(&nctx->pcb, StackSize);

    ptr((int)cctx->tid);
}

void shareCPU(int thread)
{
    // Your code here
    if (thread >= 0x02)
    {
        assert(0 && "Something went seriously wrong.");
        return;
    }

    thread_t *cctx = getThread(thread);
    thread_t *nctx = getThread((cctx->tid + 1) % 0x02);

    // Reset the base address of the stack.
    // cpy_stack will move the pointer
    // to the end.
    cctx->pcb.rsp = cctx->stk;

    ctx_save(&cctx->pcb, StackSize);
    ctx_load(&nctx->pcb);
}

void main1(int whoami)
{
    while (1)
    {
        cout << "Main 1 says Hello" << endl;
        shareCPU(whoami);
    }
}

void main2(int whoami)
{
    while (1)
    {
        cout << "Main 2 says Hello" << endl;
        shareCPU(whoami);
    }
}

int main()
{
    startThread(main1);
    startThread(main2);
    return 0;
}
