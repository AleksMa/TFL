function Dummy() {
    if (!Dummy.hasOwnProperty('singleton')) {
        Dummy.singleton = this;
        return Dummy.singleton;
    }
    return Dummy.singleton;
}

// [[;  // uncomment to get parser error

Dummy.prototype.value = 'fail';

Dummy.prototype.setValue = function (value) {
    this.value = value;
};

Dummy.prototype.getValue = function () {
    return this.value;
};


// Используем
let foo = Dummy();
let bar = Dummy();


bar.setValue(123);/*a

a*/

// Тесты
console.log('foo === bar ->', foo === bar); // true
console.log('values:', [foo.getValue(), bar.getValue()]); // [123, 123]


// Bonus
// level
baz = Dummy();
console.log('baz === bar ->', baz === bar, baz.getValue()); // true, 123

function setTimeouts() {
    for (let i = 1; i <= slen; i++) {
        setTimeout("document.z.textdisplay.value = newMake()", i * 300);
        setTimeout("window.status = newMake()", i * 300);
    }
}

let arr = [1, 2, 3];
alert(arr[0]);

var obj = {'key': 'value', "complexKey": arr};

alert(obj.key === 'value'? 1 : 2);

//alert(obj.key === 'value'? 1 ; 2);

const stressString = "some\"string\"";

alert(stressString);

function testIfs() {
    if (a) {
        return a;
    } else if (b)
        return b;
    else if (d) {
        return d;
    } else
        return c;
}


let str = 'string';

baz = {"0": 0};

const decs = function () {
    for (let i = 1; i <= slen; i++) {
        baz[i] = i * 10;
    }
};

let a = 2 * 5;

/*SOME
* M
* U
* L
* T
* ILINE
COM
MENT
*/

// №  // uncomment to get lexer err