/* ScriptInterp.h
 *
 * Copyright (C) Bryan Drewery
 *
 * This program is private and may not be distributed, modified
 * or used without express permission of Bryan Drewery.
 *
 * THIS PROGRAM IS DISTRIBUTED WITHOUT ANY WARRANTY.
 * IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY
 * FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY
 * DERIVATIVES THEREOF, EVEN IF THE AUTHORS HAVE BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE
 * IS PROVIDED ON AN "AS IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE
 * NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
 * MODIFICATIONS.
 *
 */
#ifndef _BD_SCRIPTINTERP_H
#define _BD_SCRIPTINTERP_H 1

#include "bdlib.h"
#include "String.h"
#include "Array.h"

#include <sys/types.h>

BDLIB_NS_BEGIN

/**
 * @class ScriptArgs
 * @brief Handles fetching arguments from the script interpreter in cpp command handlers
 */
class ScriptArgs {
  public:
    const size_t argc;
  protected:
  public:
    ScriptArgs() : argc(0) {};
    ScriptArgs(int _argc) : argc(_argc) {};
    virtual ~ScriptArgs() {};

    virtual size_t length() const { return argc; };

    virtual int getArgInt(int index) const = 0;
    virtual String getArgString(int index) const = 0;
};

#define SCRIPT_ERROR 1
#define SCRIPT_OK 0

#define SCRIPT_BADARGS(nl, nh, example) do {                            \
	if ((args.length() < (nl)) || (args.length() > (nh))) {         \
                return_string = "wrong # args: should be \"" +          \
                               args.getArgString(0) + (example) + "\""; \
                return SCRIPT_ERROR;                                    \
	}                                                               \
} while (0)

#define SCRIPT_FUNCTION_PROTO bd::ScriptInterp& interp, bd::String& return_string, const bd::ScriptArgs& args, bd::ScriptInterp::script_clientdata_t clientData
#define SCRIPT_FUNCTION(name) int name (SCRIPT_FUNCTION_PROTO)


/**
 * @class ScriptInterp
 * @brief Handles generalized script interpreter access
 */
class ScriptInterp {
  private:
        // Don't allow copying
        ScriptInterp(const ScriptInterp&)  {};
        ScriptInterp& operator=(const ScriptInterp&) {return *this;};

  protected:
        virtual int init() = 0;
        virtual int destroy() = 0;
        typedef intptr_t (*script_cmd_handler_t) ();

  public:
        typedef void* script_clientdata_t;
        typedef int (*script_cmd_handler_string_t)(SCRIPT_FUNCTION_PROTO);
        struct script_cmd_handler_clientdata_t {
          ScriptInterp* si;
          script_clientdata_t clientData;
          script_cmd_handler_t callback;
          script_cmd_handler_clientdata_t (ScriptInterp* _si, script_clientdata_t _clientData, script_cmd_handler_t _callback) : si(_si), clientData(_clientData), callback(_callback) {};
        };

        ScriptInterp() {};
        virtual ~ScriptInterp() {};

        /**
         * @param script The script to evaluate
         */
        virtual String eval(const String& script) = 0;

        enum LoadError {
          SCRIPT_LOAD_OK,
          SCRIPT_LOAD_ERROR,
          SCRIPT_LOAD_WRONG_INTERP
        };
        /**
         * @brief Load script file
         * @param fileName The file to load
         * @param resultStr String to hold error output from interp
         */
        virtual LoadError loadScript(const String& fileName, String& resultStr) = 0;

        /**
         * @param name Name of the command to create
         * @param callback The script_cmd_handler_t function to call when the command is ran
         */
        virtual void createCommand(const String& name, script_cmd_handler_string_t callback, script_clientdata_t clientData = NULL) = 0;

        /**
         * @brief Remove a command from the interp
         * @param name The name of the command to remove
         */
        virtual void deleteCommand(const String& name) = 0;

        /**
         * @brief Remove a variable from the interp
         * @param name The name of the variable to remove
         */
        virtual void unlinkVar(const String& name) {};

        /**
         * @brief Return the class name as a String
         * This is only needed for calling specialized template methods from the derived class. See Unit Tests for examples.
         * @sa http://stackoverflow.com/questions/2914081/c-member-function-template-in-derived-class-how-to-call-it-from-base-class
         */
        virtual String type() const = 0;
};


BDLIB_NS_END
#endif /* _BD_SCRIPTINTERP_H */
