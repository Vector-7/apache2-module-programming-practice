function request() {
    var n1 = $('#n1').val();
    var n2 = $('#n2').val();

    if (!(n1 && n2)) alert("error");
    else {
        $.ajax({
            type: "GET",
            url: `http://localhost/cal?n1=${n1}&n2=${n2}`,
            success: (d) => {
                const v = d.split(':');
                const sig = v[0];
                const val = parseInt(v[1]);

                if(sig == "ok") $('#res').text(val);
                else alert("GOT ERROR");
            }
        });
    }
}