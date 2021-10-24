var spec_w = [];
var spec_b = [];
var spec_r = [];
var spec_g = [];
var spec_f = [];
var spec_CA = [];
var spec_CB = [];
var spec_BC = [];
var spec_labels = [];
var spec_preset = {};
var spec_lin = 2.9612;
var par_b = 54;
var par_r = 54;
var par_g = 36;
var par_f = 6;
var max_curr = 30;

function draw_chart() {
    ctx = document.getElementById("spectrumChart").getContext('2d');
    items_b = [];
    items_r = [];
    items_g = [];
    items_f = [];
    var itm_count = 0;
    while (itm_count < spec_b.length) {
      /**  items_ca.push({"x":spec_w[itm_count],"y":spec_CA[itm_count]});
        items_cb.push({"x":spec_w[itm_count],"y":spec_CB[itm_count]});
        items_bc.push({"x":spec_w[itm_count],"y":spec_BC[itm_count]});
**/
        items_b.push({"x":spec_w[itm_count],"y":spec_b[itm_count]});
        items_g.push({"x":spec_w[itm_count],"y":spec_g[itm_count]});
        items_r.push({"x":spec_w[itm_count],"y":spec_r[itm_count]});
        items_f.push({"x":spec_w[itm_count],"y":spec_f[itm_count]});
        itm_count = itm_count + 1;
    }
    window.spectrum_chart = new Chart(ctx, {
    type: 'line',
    
    options: {
        plugins: {
            title: {
                display: false,
                text: 'Spectrum Output'
            }
        },
        scales: {
            x: {
                type: 'linear',
                
                
            },
            y: {
                type: 'linear'
            }
        }
    },
    data: {
        datasets: [
            {
                label: "Deep Blue",
                data: items_b,
                borderColor: '#4800FF',
                backgroundColor: 'rgba(72,0,255,0.9)',
            },
            {
                label: "Deep Red",
                data: items_r,
                borderColor: '#FF009D',
                backgroundColor: 'rgba(255,0,177,0.5)',
            },
            {
                label: "Green",
                data: items_g,
                borderColor: '#26FF00',
                backgroundColor: 'rgba(38,255,0,0.5)',
                showLine: true
            },
            {
                label: "Far Red",
                data: items_f,
                borderColor: '#FF004D',
                backgroundColor: 'rgba(255,0,77,0.5)',
                showLine: true
            }
            
        ]
    }
})
};

function update_chart() {
    var b_au = (($("#blueRange")[0].value) / par_b)*spec_lin;
    var r_au = (($("#redRange")[0].value) / par_r)*spec_lin;
    var g_au = (($("#greenRange")[0].value) / par_g)*spec_lin;
    var f_au = (($("#farRange")[0].value) / par_f)*spec_lin;
        items_b = [];
    items_r = [];
    items_g = [];
    items_f = [];
    var itm_count = 0;
    while (itm_count < spec_b.length) {
      /**  items_ca.push({"x":spec_w[itm_count],"y":spec_CA[itm_count]});
        items_cb.push({"x":spec_w[itm_count],"y":spec_CB[itm_count]});
        items_bc.push({"x":spec_w[itm_count],"y":spec_BC[itm_count]});
**/
        items_b.push({"x":spec_w[itm_count],"y":spec_b[itm_count]*b_au});
        items_g.push({"x":spec_w[itm_count],"y":spec_g[itm_count]*g_au});
        items_r.push({"x":spec_w[itm_count],"y":spec_r[itm_count]*r_au});
        items_f.push({"x":spec_w[itm_count],"y":spec_f[itm_count]*f_au});
        itm_count = itm_count + 1;
    }
    window.spectrum_chart.data.datasets[0].data = items_b;
    window.spectrum_chart.data.datasets[1].data = items_r;
    window.spectrum_chart.data.datasets[2].data = items_g;
    window.spectrum_chart.data.datasets[3].data = items_f;
    window.spectrum_chart.update();
  
};
function update_ctrl() {
        $("#loadedProfile")[0].value = spec_preset["n"];
        $("#blueRange")[0].value = spec_preset["b"];
        $("#redRange")[0].value = spec_preset["r"];
        $("#greenRange")[0].value = spec_preset["g"];
        $("#farRange")[0].value = spec_preset["f"];
        if (spec_preset["s"] == "s") {
            $("#profileSource")[0].value = "System Profile";
        } else {
            $("#profileSource")[0].value = "User Profile";
        };
        
};

function setup_profiles() {
    $.ajax({
    "url":"/api/spec/profile.csv",
    "crossDomain":true  
    }).done(function( data ){
        var cut_string = data.split(",");  
       
        spec_preset = {"n":cut_string[0],"s":cut_string[1],"b":((cut_string[2])/100)*30,"g":((cut_string[4])/100)*25,"r":((cut_string[3])/100)*30,"f":((cut_string[5])/100)*4.2};
        update_ctrl();
        draw_chart();
        update_chart();

    });
};

function enable_control() {
    if ($("#automaticControl")[0].checked == false) {
        $("#blueRange")[0].disabled = false;
        $("#redRange")[0].disabled = false;
        $("#greenRange")[0].disabled = false;
        $("#farRange")[0].disabled = false;
        $("#auWarning")[0].style.display = 'block';
        $.get("/api/spec/auto_off.json");
    } else {
        $("#blueRange")[0].disabled = true;
        $("#redRange")[0].disabled = true;
        $("#greenRange")[0].disabled = true;
        $("#farRange")[0].disabled = true;
        $("#blueRange")[0].value = spec_preset["b"];
        $("#redRange")[0].value = spec_preset["r"];
        $("#greenRange")[0].value = spec_preset["g"];
        $("#farRange")[0].value = spec_preset["f"];
        $("#auWarning")[0].style.display = 'none';
        update_chart();
        $.get("/api/spec/auto_on.json");
    }
    
};
$.ajax({
    "url":"/res/csv/spectrum.csv",
    "crossDomain":true    
    }).done(function( data ){
    var all_rows = data.split("\n");
    var count = 1;
    var cut_count = 0;
    cut_string = all_rows[0].split(",");
    while (cut_count<cut_string.length) {
        spec_labels.push(cut_string[cut_count]);
        cut_count = cut_count + 1;
    }
    while(count<all_rows.length) {
    cut_string = all_rows[count].split(",");
    var cut_count = 0;
    while (cut_count<cut_string.length) {
        var num = Number(cut_string[cut_count]);
        if (cut_count == 0) {
            // Wavelength:
            spec_w.push(num);
        } else if (cut_count == 1)  {
            // Blue:
            spec_b.push(num);
        } else if (cut_count == 2)  {
            // Green:
            spec_g.push(num);
        } else if (cut_count == 3)  {
            // (Deep) Red:
            spec_r.push(num);
        } else if (cut_count == 4)  {
            // (Far) Red:
            spec_f.push(num);
        } else if (cut_count == 5)  {
            // Chlorophyll A:
            spec_CA.push(num);
        }  else if (cut_count == 6)  {
            // Chlorophyll B:
            spec_CB.push(num);
        }  else if (cut_count == 7)  {
            // Beta-Carotenes:
            spec_BC.push(num);
        }
        
        cut_count = cut_count+1;
    }

    count = count+1;
    }
    setup_profiles();
});

function update_from_sys() {
        if ($("#automaticControl")[0].checked == true) {
          $.ajax({
            "url":"/api/spec/profile.csv",
            "crossDomain":true  
            }).done(function( data ){
                var cut_string = data.split(",");  
                spec_preset = {"n":cut_string[0],"s":cut_string[1],"b":((cut_string[2])/100)*30,"g":((cut_string[4])/   100)*25,"r":((cut_string[3])/100)*30,"f":((cut_string[5])/100)*4.2};
                update_ctrl();
            });
       };
};

window.dashInt = window.setInterval(update_from_sys,30000);
