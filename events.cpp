#include "events.h"

Events::Events()
{
    startTime.setHMS(0, 0, 0);
    endTime.setHMS(0, 0, 0);
    title = "";
    note = "";
    away.clear();
    NoteEndTime = 1;
}
