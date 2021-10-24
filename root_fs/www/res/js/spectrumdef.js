_spectrumEdit = function(){
    var ctx = false;
    var chart = false;
    var program = [
    ];
    var profile_id = false;
    var profile_name = false;
    var profiles = false;
    var vars = {
        volts: 30,
        br: "#blueRange",
        rr: "#redRange",
        gr: "#greenRange",
        fr: "#farRange",
        pm: "#pomax_alert",
        btn: "#create_btn",
        fmt: "HH:mm",
        tbl: "#editor_table",
        can: "spectrumChart",
        load: "#loadModal",
        prs: "#load_profile"
    };
    
    this.construct = function(options){
        $.extend(vars , options);
        _initGraph();
        
    };
    
     this.checkModal = function(event){
        p_blue = $(vars["br"])[0].value*vars["volts"];
        b_pct = Math.round(($(vars["br"])[0].value/$(vars["br"])[0].max)*100,2);
        p_red = $(vars["rr"])[0].value*vars["volts"];
        r_pct = Math.round(($(vars["rr"])[0].value/$(vars["rr"])[0].max)*100,2);
        p_green = $(vars["gr"])[0].value*vars["volts"];
        g_pct = Math.round(($(vars["gr"])[0].value/$(vars["gr"])[0].max)*100,2);
        p_far = $(vars["fr"])[0].value*vars["volts"];
        f_pct = Math.round(($(vars["fr"])[0].value/$(vars["fr"])[0].max)*100,2);
        p_total = p_blue+p_red+p_green+p_far;
        $("#db_pct")[0].innerHTML = b_pct;
        $("#dr_pct")[0].innerHTML = r_pct;
        $("#gr_pct")[0].innerHTML = g_pct;
        $("#fr_pct")[0].innerHTML = f_pct;
        $("#watts_total")[0].innerHTML = p_total;
        if (p_total > 1100) {
        $(vars["pm"]).addClass('alert-danger');
        $(vars["btn"]).addClass('bg-danger');
        $(vars["btn"]).disabled = true;
        } else {
        $(vars["pm"]).removeClass('alert-danger');
        $(vars["btn"]).removeClass('bg-danger');
        $(vars["btn"]).disabled = false;
        }
     };
     this._initGraph = function () {
         /** Init chart: **/
        items_b = [];
        items_r = [];
        items_g = [];
        items_f = [];
         ctx = document.getElementById(vars["can"]).getContext('2d');
         chart = new Chart(ctx, {
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
                        type: 'time',
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
                ]}});
         $.get("/api/spec/index.json",function(d,e){
             profiles = d.spectrum.profiles;
             for (k in profiles) {
                 var option = new Option(d.spectrum.profiles[k], k); $(vars["prs"]).append($(option));
             };
             $(vars["load"]).modal('show');
         });
         $(vars["load"]).modal('show');
         program = [];
     };
     this._updateTable = function() {
         /** This function actually updates the table and the graphs. just made more sense. **/
        
        /** graph variables: **/
        items_b = [];
        items_r = [];
        items_g = [];
        items_f = [];
        /** Table stepper (which also updates items): **/
        $("#append").empty();
        var count = 1;
        for (p in program) {
            

            var tr = $("<tr/>");
            $("#append").append(tr);
            var th = $("<th/>").attr({"scope":"row"});
            
            th[0].innerHTML = "#"+count;
            tr.append(th);
            var td = $("<td/>");
            td[0].innerHTML = program[p].start;
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].end;
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].b+"%";
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].g+"%";
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].r+"%";
            tr.append(td[0]);
            var td = $("<td/>");
            td[0].innerHTML = program[p].f+"%";
            tr.append(td[0]);
            var this_day = new Date();
            var start_time = this_day.getDay()+"/"+this_day.getMonth()+"/"+this_day.getYear()+" "+program[p].start;
            items_b.push({"y":program[p].b,"x":start_time});
            items_g.push({"y":program[p].g,"x":start_time});
            items_r.push({"y":program[p].r,"x":start_time});
            items_f.push({"y":program[p].f,"x":start_time});
            count = count +1;
        }
        chart.data.datasets[0].data = items_b;
        chart.data.datasets[1].data = items_r;
        chart.data.datasets[2].data = items_g;
        chart.data.datasets[3].data = items_f;
        chart.update();
    
     };
     

     
     this.createStep= function(event) {
         $("#time_alert").addClass('d-none');
         start = $('#starttime').datetimepicker('viewDate');
         end = $('#endtime').datetimepicker('viewDate');
         if (start.format(vars["fmt"]) == end.format(vars["fmt"])) {
             $("#time_alert").removeClass('d-none');
            event.preventDefault();
             return false;
         }
         /** Now construct the step object: **/
         step = {
             "start":start.format(vars["fmt"]),
             "end":end.format(vars["fmt"]),
             "b": b_pct,
             "g": g_pct,
             "r": r_pct,
             "f": f_pct
         }
        len = program.length;
         program[len] = step;

         this._updateTable();
         //event.trigger();
         $("#addStepModal").modal('hide');
         
     };
     
     this.createSpectrum = function(event) {
         s_val = $("#load_profile")[0].value;
         n_val = $("#new-profile")[0].value;
         if ((s_val == "")&&(n_val == "")) {
             alert("Type in a new name or select an existing profile.");
             return false;
         };
         // New Value: 
         if (s_val == "" ) {
             token = n_val.replaceAll(" ","");
             pkeys = Object.keys(profiles);
             window.pkeys = pkeys;
             if(pkeys.includes(token) == true) {
                 alert("Name Already in use; Please type in a different name.");
                 return false;
             };
             
             profiles[token] = n_val;
             profile_id = token;
             profile_name = n_val;
             $("#loadedProfile")[0].value = n_val;
             $(vars["load"]).modal('hide');
             $("#e_add")[0].disabled = false;
             $("#e_save")[0].disabled = false;
             $("#e_down")[0].disabled = false;
             $("#e_up")[0].disabled = false;
         } else {
             // Existing Value:
             profile_id = s_val;
             profile_name = profiles[profile_id];
             $("#loadedProfile")[0].value = profile_name;
         };
            
    };
    
    this.saveSpectrum = function() {
        output = new Object();
        output.type="profile";
        output.id = profile_id;
        output.name = profile_name;
        output.steps = program;
        output.count = program.length;
        return JSON.stringify(output);
    };
    
     
};

