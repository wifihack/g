#include <iostream>
#include <GErr>

using namespace std;

struct Obj {
  GErr& err() {

    return err_;
  }
private:
  GStdErr err_ { g::FAIL, "NOT_SUPPORTED in Obj class" };
};

int main() {
  {
    GStdErr err;
    clog << err << endl;
  }

  {
    GStdErr err{ g::NOT_SUPPORTED };
    clog << err << endl;
  }

  {
    GStdErr err { g::NOT_SUPPORTED, "NOT_SUPPORTED" };
    clog << err << endl;
  }

  {
    Obj obj;
    GErr& err = obj.err();
    clog << err << endl;
  }
}
