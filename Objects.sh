function objects
{
    local IFS=$'\n'
    echo "${obj[*]}" | sed -e 's| |\\ |g' -e 's|.cc$|.o|' | tr '\n' ' ' # -e 's|\([^/]*$\)|.\1|'
}

function nonunit
{
    obj=(sources/**/!(unit|*.unit).cc)
    objects
}

function unit
{
    obj=(sources/**/!(main).cc)
    objects
}

