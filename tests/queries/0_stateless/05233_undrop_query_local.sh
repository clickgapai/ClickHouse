#!/usr/bin/env bash

CUR_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
# shellcheck source=../shell_config.sh
. "$CUR_DIR"/../shell_config.sh

# A table dropped in clickhouse-local stays in system.dropped_tables, but UNDROP cannot bring it
# back there: it must say so with UNKNOWN_TABLE instead of failing with a logical error.
${CLICKHOUSE_LOCAL} -q "create table t (id Int32) Engine=MergeTree() order by id; drop table t; select count() from system.dropped_tables where table = 't';"
${CLICKHOUSE_LOCAL} -q "create table t (id Int32) Engine=MergeTree() order by id; drop table t; undrop table t;" 2>&1 | grep -Faq "UNKNOWN_TABLE" && echo OK
