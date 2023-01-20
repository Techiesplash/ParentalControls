#include <string>
#include <iostream>
#include "test.h"
#include "../reusable/reusable.h"
#include <vector>
#include <string>
#include <thread>
#include <chrono>

bool IsDummyProgramBeingKilled()
{
    system("./testdummyprogram </dev/null &>/dev/null &");
    std::this_thread::sleep_for(std::chrono::milliseconds(850));
    FILE* fp = fopen("./foo.msg", "w");
    if(fp)
    {
        fclose(fp);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    fp = fopen("./bar.msg", "r");
    if(fp)
    {
        remove("foo.msg");
        remove("bar.msg");
        fclose(fp);
        return false;
        system("killall testdummyprogram");
    }
    remove("foo.msg");
    remove("bar.msg");
    return true;
}

void SaveKillList(std::vector<std::string> data)
{
    remove("/pc.list");
    FILE *fp = fopen("/pc.list", "w");
    if (fp != NULL)
    {

        for (int i = 0; i < (int)data.size(); i++)
        {
            fputs(std::string(data[i]).c_str(), fp);
        }

        fclose(fp);

        RefreshKillList();
    }
}

void StartDaemon()
{
    system("./parentald </dev/null &>/dev/null &");
}

void StopDaemon()
{
    system("killall parentald");
}

int main()
{
    StopDaemon();
    remove("/testing.thing");
    FILE *fp = fopen("/testing.thing", "w");
    if (fp)
    {
        fclose(fp);
        remove("/testing.thing");
    }
    else
    {
        exit(0);
    }
    // Back up list
    system("cp /pc.list ./pc.list");

    // Create list
    std::vector<std::string> d;
    d.push_back("testdummyprogram");
    SaveKillList(d);

    // Start the daemon and detach
    StartDaemon();

    // Test the status
    tCase("Status Check Test");
    
    // Try deactivating it
    tAssert(Deactivate(), "Did the daemon respond when telling it to stop?");

    int status = GetDaemonStatus();

    tAssert(status != DaemonStatus::ERROR, "Did the daemon respond?");
    tAssert(status == DaemonStatus::OFF, "Did the daemon stop when it was told to?");

    // Try reactivating it
    tAssert(Activate(), "Did the daemon respond when telling it to start?");

    status = GetDaemonStatus();

    tAssert(status != DaemonStatus::ERROR, "Did the daemon respond?");
    tAssert(status == DaemonStatus::ON, "Did the daemon start when it was told to?");

    tFinishTest();

    tCase("Auto-Enable Test");

    // Try disabling auto-enable
    fp = fopen("/pc.startdisabled", "w");
    if (FileExists("/pc.startdisabled"))
    {
        fclose(fp);
    }
    StopDaemon();
    StartDaemon();

    status = GetDaemonStatus();

    tAssert(status != DaemonStatus::ERROR, "Did the daemon respond after restart?");
    tAssert(status == DaemonStatus::OFF, "Did the daemon not enable automatically?");
    
    // Try enabling auto-enable
    remove("/pc.startdisabled");
    StopDaemon();
    StartDaemon();

    status = GetDaemonStatus();
    
    tAssert(status != DaemonStatus::ERROR, "Did the daemon respond after restart?");
    tAssert(status == DaemonStatus::ON, "Did the daemon enable automatically?");

    tFinishTest();

    tCase("Program Killing Test");

    Activate();
    tAssert(IsDummyProgramBeingKilled(), "Is the test program being killed while the daemon is enabled?");
    
    Deactivate();
    tAssert(!IsDummyProgramBeingKilled(), "Is the test program being not killed while the daemon is disabled?");

    tFinishTest();


    // Clean up
    system("killall testdummyprogram");
    StopDaemon();
    system("cp ./pc.list /pc.list");
    remove("./pc.list");

    // Start it again in case it was already installed
    system("systemctl start parentald");
    

    return !tPrintTotalScore();
}