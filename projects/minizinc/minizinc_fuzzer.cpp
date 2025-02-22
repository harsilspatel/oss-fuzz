#include <minizinc/solver.hh>

using namespace std;
using namespace MiniZinc;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    Timer starttime;
    bool fSuccess = false;
    try {
      MznSolver slv(std::cout,std::cerr);
      try {
        std::string model = std::string(reinterpret_cast<const char*>(Data), Size);
        std::vector<std::string> args({"-c","--solver","org.minizinc.mzn-fzn"});
        fSuccess = (slv.run(args, model, "minizinc", "model.mzn") != SolverInstance::ERROR);
      } catch (const LocationException& e) {
        if (slv.get_flag_verbose())
          std::cerr << std::endl;
        std::cerr << e.loc() << ":" << std::endl;
        std::cerr << e.what() << ": " << e.msg() << std::endl;
      } catch (const Exception& e) {
        if (slv.get_flag_verbose())
          std::cerr << std::endl;
        std::string what = e.what();
        std::cerr << what << (what.empty() ? "" : ": ") << e.msg() << std::endl;
      }
      catch (const exception& e) {
        if (slv.get_flag_verbose())
          std::cerr << std::endl;
        std::cerr << e.what() << std::endl;
      }
      catch (...) {
        if (slv.get_flag_verbose())
          std::cerr << std::endl;
        std::cerr << "  UNKNOWN EXCEPTION." << std::endl;
      }

      if (slv.get_flag_verbose()) {
        std::cerr << "   Done (";
        cerr << "overall time " << starttime.stoptime() << ")." << std::endl;
      }
    } catch (const Exception& e) {
      std::string what = e.what();
      std::cerr << what << (what.empty() ? "" : ": ") << e.msg() << std::endl;
    }

  return 0;  // Non-zero return values are reserved for future use.
}
