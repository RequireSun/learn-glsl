#!/usr/bin/env bash
BASEDIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

serve ${BASEDIR}/build -p 8877
