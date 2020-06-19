pub(crate) struct MusicXSD {
    type_definitions: Vec<TypeDefinition>,
}

impl MusicXSD {
    pub fn new(type_definitions: Vec<TypeDefinition>) -> Self {
        Self { type_definitions }
    }
}

impl MusicXSD {
    pub(crate) fn enumerations(&self) -> Vec<Enumeration> {
        let mut result = Vec::new();
        for t in &self.type_definitions {
            if let TypeDefinition::Simple(simple_type) = t {
                if let SimpleType::Enum(enumeration) = simple_type {
                    result.push(enumeration.clone());
                }
            }
        }
        result.sort_by(|a, b| Ord::cmp(&a.name, &b.name));
        result
    }
}

pub(crate) enum TypeDefinition {
    Simple(SimpleType),
}

pub(crate) enum SimpleType {
    Enum(Enumeration),
}

#[derive(Clone)]
pub(crate) struct Enumeration {
    pub(crate) index: usize,
    pub(crate) id: String,
    pub(crate) name: String,
    pub(crate) base: String,
    pub(crate) documentation: String,
    pub(crate) members: Vec<String>,
}

impl Default for Enumeration {
    fn default() -> Enumeration {
        Enumeration {
            index: 0,
            id: String::default(),
            name: String::default(),
            base: String::default(),
            documentation: String::default(),
            members: Vec::new(),
        }
    }
}
