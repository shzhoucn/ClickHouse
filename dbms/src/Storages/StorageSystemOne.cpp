#include <DB/Core/Exception.h>
#include <DB/Core/ErrorCodes.h>

#include <DB/Columns/ColumnsNumber.h>
#include <DB/DataTypes/DataTypesNumberFixed.h>
#include <DB/DataStreams/OneBlockInputStream.h>
#include <DB/Storages/StorageSystemOne.h>


namespace DB
{


StorageSystemOne::StorageSystemOne(const std::string & name_)
	: name(name_)
{
	columns.push_back(NameAndTypePair("dummy", new DataTypeUInt8));
}


BlockInputStreams StorageSystemOne::read(
	const Names & column_names, ASTPtr query, QueryProcessingStage::Enum & processed_stage, size_t max_block_size, unsigned threads)
{
	check(column_names);
	processed_stage = QueryProcessingStage::FetchColumns;

	Block block;
	ColumnWithNameAndType col;
	col.name = "dummy";
	col.type = new DataTypeUInt8;
	col.column = new ColumnConstUInt8(1, 0);
	block.insert(col);
	
	return BlockInputStreams(1, new OneBlockInputStream(block));
}


}
