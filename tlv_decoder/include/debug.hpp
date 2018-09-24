/*++
Author : James Marjun Jallorina
Contact: jamesmarjun[dot]jallorina[at]yahoo[dot]com[dot]ph

This program is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation, either version
3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.
If not, see <http://www.gnu.org/licenses/>.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
See the file 'LICENSE' for complete copying permission.

Module Name:
    debug.hpp
Abstract:
    This module serves as a debug utility in a file for logging purpose
--*/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C"{
#endif

extern int app_name_init(char *app_name);
extern int debugOn(char *filename);
extern int printInfo(const char *format, ...);
extern int printDebug(const char *format, ...);
extern int printWarn(const char *format, ...);
extern int printFatal(const char *format, ...);
extern int printError(const char *format, ...);
#ifdef __cplusplus
}
#endif

#endif 	//_DEBUG_H_