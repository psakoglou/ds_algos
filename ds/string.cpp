#include <iostream>
#include <initializer_list>
#include <cstring>

namespace
{

	class String
	{
	private:
		char *m_data = nullptr;
		std::size_t m_size = 0;
		std::size_t m_idx = 0;

	public:
		// constructors

		String() = default;

		String(std::initializer_list<char> init)
		{
			m_size = init.size();
			m_data = new char[m_size];
			std::memcpy(m_data, init.begin(), m_size);
			m_idx = 0;
		}

		String(const String &s)
		{
			std::size_t size = s.m_size;
			m_data = new char[size];
			m_size = size;
			m_idx = s.m_idx;
			std::memcpy(m_data, s.m_data, size);
		}

		String(std::size_t size)
		{
			m_data = new char[size];
			m_size = size;
			m_idx = 0;
		}

		// destructor

		~String()
		{
			if (m_data != nullptr)
			{
				delete[] m_data;
			}
		}

		// operators

		String &operator=(const String &s)
		{
			if (m_data != s.m_data)
			{
				if (m_data != nullptr)
				{
					delete[] m_data;
				}
				m_data = new char[s.m_size];
				m_idx = s.m_idx;
				m_size = s.m_size;
				std::memcpy(m_data, s.m_data, m_size);
			}
			return *this;
		}

		const bool isEmpty()
		{
			return m_size == 0 || m_data == nullptr;
		}

		const std::size_t size()
		{
			return m_size;
		}

		const char *data()
		{
			return m_data;
		}

		const std::size_t index()
		{
			return m_idx;
		}

		friend std::ostream &operator<<(std::ostream &ostream, String const &s)
		{
			return ostream.write(s.m_data, s.m_size);
		}

		// procedures

		void insertAt(char a, int pos)
		{
			if (pos > m_idx || pos < 0)
			{
				std::out_of_range("pos out of bounds");
				return;
			}

			if (m_data == nullptr && m_size == 0)
			{
				m_size = 10;
				m_data = new char[m_size];
			}

			if (m_idx + 1 >= m_size) // is at capacity
			{
				char *temp = new char[m_size];
				std::memcpy(temp, m_data, m_size);
				std::size_t newSize = m_size * 2;
				delete[] m_data;
				m_data = new char[newSize];
				std::memcpy(m_data, temp, newSize);
				delete[] temp;
				m_size = newSize;
			}

			// [ a  b  c  d  e ] -> insert k at 2 -> [ a  b  k  c  d  e ]
			// char *temp = new char[m_idx + 1];
			// std::memcpy(temp, m_data, pos);
			// m_data[pos] = a;
			// std::memcpy(m_data + pos + 1, temp, 0);
			std::memmove(m_data + pos + 1, m_data + pos, sizeof(char) * (m_idx - pos));
			m_data[pos] = a;
		}

		void push_back(char a)
		{
			if (m_data == nullptr && m_size == 0)
			{
				m_size = 10;
				m_data = new char[m_size];
			}
			if (m_idx >= m_size)
			{
				char *temp = new char[m_size];
				std::memcpy(temp, m_data, m_size);
				std::size_t newSize = m_size * 2;
				delete[] m_data;
				m_data = new char[newSize];
				std::memcpy(m_data, temp, m_size);
				delete[] temp;
				m_size = newSize;
			}
			m_data[m_idx++] = a;
		}

		void print()
		// space: O(1), we can parse data in the existing memory chunch
		// time: O(n), n: m_size
		{
			if (m_size == 0 || m_data == nullptr)
			{
				return;
			}
			for (int i = 0; i < m_idx; i++)
			{
				std::cout << m_data[i] << ((i + 1 >= m_idx) ? " " : ", ");
			}
			std::cout << std::endl;
		}

		// reverse
		String reverse()
		{
			if (m_data == nullptr || m_size < 2)
			{
				return *this;
			}
			int i = 0;
			int j = m_size - 1;
			while (i < j)
			{
				std::swap(m_data[i], m_data[j]);
				i++;
				j--;
			}
			return *this;
		}

		String insertionSortInNewArray()
		{
			if (m_data == nullptr || m_size < 2)
			{
				return *this;
			}
			String sorted(m_size);
			sorted.m_data[0] = m_data[0];
			for (int i = 1; i < m_size; i++)
			{
				char key = m_data[i]; // insert key in a sorted list
				int j = i - 1;
				while (j >= 0 && key < sorted.m_data[j])
				{
					sorted.m_data[j + 1] = sorted.m_data[j];
					j--;
				}
				sorted.m_data[j + 1] = key;
			}
			return sorted;
		}

		bool isPalindrome()
		{
			if (m_data == nullptr || m_size == 0)
			{
				return false;
			}
			int i = 0;
			int j = m_size - 1;
			while (i < j)
			{
				if (m_data[i] != m_data[j])
				{
					return false;
				}
				i++;
				j--;
			}
			return true;
		}

		bool elemExists(char c)
		{
			if (m_data == nullptr || m_size == 0)
			{
				return false;
			}
			for (int i = 0; i < m_size; i++)
			{
				if (c == m_data[i])
				{
					return true;
				}
			}
			return false;
		}

		// insertion sort
		String insertionSortInPlace()
		{
			if (m_data == nullptr || m_size < 2)
			{
				return *this;
			}
			for (int i = 1; i < m_size; i++)
			{
				char key = m_data[i]; // insert key in a sorted list
				int j = i - 1;
				while (j >= 0 && key < m_data[j])
				{
					m_data[j + 1] = m_data[j];
					j--;
				}
				m_data[j + 1] = key;
			}
			return *this;
		}

	private:
		void _merge(char *m_data, int p, int q, int r)
		{
			int n1 = q - p;
			int n2 = r - q;
			char *s1 = new char[n1];
			char *s2 = new char[n2];
			for (int i = 0; i < n1; i++)
			{
				s1[i] = m_data[p + i];
			}
			for (int i = 0; i < n2; i++)
			{
				s2[i] = m_data[q + i];
			}
			int i = 0;
			int j = 0;
			int k = p;
			while (i < n1 && j < n2)
			{
				if (s1[i] < s2[j])
				{
					m_data[k++] = s1[i++];
				}
				else
				{
					m_data[k++] = s2[j++];
				}
			}
			while (i < n1)
			{
				m_data[k++] = s1[i++];
			}
			while (j < n2)
			{
				m_data[k++] = s2[j++];
			}
			delete[] s1;
			delete[] s2;
		}

		void _mergesort(char *m_data, int p, int r)
		{
			if (r - p < 2)
			{
				return;
			}
			if (p < r)
			{
				int q = std::floor(p + ((r - p) / 2));
				_mergesort(m_data, p, q);
				_mergesort(m_data, q, r); // 22 louse point
				_merge(m_data, p, q, r);
			}
		}

	public:
		String mergesort()
		{
			_mergesort(m_data, 0, m_size - 1);
			return *this;
		}
	};

} // namespace

int main()
{

	String p;
	for (int i = 0; i < 11; i++)
	{
		p.push_back('a' + i);
	}
	p.print();
	p.insertAt('z', -1);
	p.insertAt('z', 0);
	p.insertAt('z', 2);
	p.insertAt('z', 3);
	p.insertAt('z', 10000);
	p.print();

	String s(10);
	String s2(s);
	String s3 = {'a'};
	String s33 = {'a', 'b', 'c'};
	String s333 = {'a', 'b', 'a'};
	String s3333 = {'a', 'c', 'c', 'a'};

	// std::cout << std::boolalpha << s3.isPalindrome() << std::endl;
	// std::cout << std::boolalpha << s33.isPalindrome() << std::endl;
	// std::cout << std::boolalpha << s333.isPalindrome() << std::endl;
	// std::cout << std::boolalpha << s3333.isPalindrome() << std::endl;

	String s4 = {'c', 'd', 'a', 'b', 'a', 'a', 'j', 'z'};
	String s5 = {'c', 'd', 'a', 'b', 'a', 'a', 'j', 'z'};

	std::cout << s4.mergesort() << std::endl;

	// std::cout << s4.insertionSortInPlace() << std::endl;
	// std::cout << s5.insertionSortInNewArray() << std::endl;

	// std::cout << std::boolalpha << s3.elemExists('a') << std::endl;
	// std::cout << std::boolalpha << s4.elemExists('a') << std::endl;
	// std::cout << std::boolalpha << s4.elemExists('k') << std::endl;

	return 0;
}
