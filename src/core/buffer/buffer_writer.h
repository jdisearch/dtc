/*
* Copyright [2021] JD.com, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __CACHE_WRITER_H
#define __CACHE_WRITER_H

#include "buffer_pond.h"
#include "table/table_def.h"
#include "writer_interface.h"
#include "raw_data_process.h"

class BufferWriter : public WriterInterface, public BufferPond {
    private:
	RawData *pstItem;
	DataProcess *pstDataProcess;
	int iIsFull;
	int iRowIdx;
	Node stCurNode;
	char achPackKey[MAX_KEY_LEN + 1];
	char szErrMsg[200];

    protected:
	int AllocNode(const RowValue &row);

    public:
	BufferWriter(void);
	~BufferWriter(void);

	int cache_open(BlockProperties *pstInfo,
		       DTCTableDefinition *p_table_definition_);

	const char *err_msg()
	{
		return szErrMsg;
	}
	int begin_write();
	int full();
	int write_row(const RowValue &row);
	int commit_node();
	int rollback_node();
};

#endif
