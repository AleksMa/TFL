function Dummy() {
    if (!Dummy.hasOwnProperty) {
        Dummy.singleton = this;
        return Dummy.singleton;
    }
    return Dummy.singleton;
}

//№a
/*
MULTI
LINE
COMMENT */

Dummy.prototype.value = 'fail';

Dummy.prototype.setValue = function (value) {
    this.value = value;
};

Dummy.prototype.getValue = function () {
    return this.value;
};


// Используем
let foo = new Dummy;
let bar = new Dummy;


bar.setValue(123);

// Тесты
console.log('foo === bar ->', foo === bar); // true
console.log('values:', [foo.getValue, bar.getValue]); // [123, 123]


// Bonus
// level
baz = Dummy;
console.log('baz === bar ->', baz === bar, baz.getValue()); // true, 123

function setTimeouts() {
    for (var i = 1; i <= slen; i++) {
        setTimeout("document.z.textdisplay.value = newMake()", i * 300);
        setTimeout("window.status = newMake()", i * 300);
    }
}

const stressString = "some\"string\"";
