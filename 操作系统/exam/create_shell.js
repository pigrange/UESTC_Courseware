var shell_num = 20

var process = []

var pid = 0;

for (var i = 0; i < shell_num; i++){
	var shell = Math.ceil(Math.random() * 15);
	switch(true){
		// cr
		case shell<6:
			var random = Math.random();
			var priority;
			if (random > 0.5) {
				priority = 2;
			}else{
				priority = 1;
			}
			console.log(`cr ${String.fromCharCode(65+pid)} ${priority}`)
			process.push(String.fromCharCode(65+pid))
			pid++; 
			break;
		// to
		case shell>=6 && shell<10:
			console.log('to');
			break;
		case shell>=10 && shell<15:
			var resource = Math.ceil(Math.random() * 4)
			var num = Math.ceil(Math.random() * resource)
			console.log(`req R${resource} ${num}`);
			break;
		case shell==15:
			var random = Math.floor(Math.random() * process.length);
			console.log(`de ${process[random]}`);
			process.splice(random, 1);
			break;
	}
}